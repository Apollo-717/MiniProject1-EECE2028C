#include "../include/DoubleyLinkedList.h"
#include "../include/Student.h"
#include <iostream>
#include <filesystem>
#include <limits>

void Check(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}
template <typename F>
void Reject(F action) {
    bool rejected = false;
    try { action(); } catch (const std::exception&) { rejected = true; }
    Check(rejected, "Expected an error");
}
Student* Make(const std::string& number) {
    return new Student("Test", "Student", number, 2000, 2, 29, 3.5);
}
struct Tracked {
    static inline int alive = 0;
    int value;
    explicit Tracked(int value) : value(value) { ++alive; }
    Tracked(const Tracked& other) : value(other.value) { ++alive; }
    ~Tracked() { --alive; }
    bool operator<(const Tracked& other) const { return value < other.value; }
    bool operator>(const Tracked& other) const { return value > other.value; }
    bool operator==(const Tracked& other) const { return value == other.value; }
};

int main() {
    try {
        using List = DoubleyLinkedList<Student>;
        List list;
        Check(list.IsEmpty() && list.Size() == 0, "Empty state");
        Check(!list.GetLargest() && !list.GetSmallest(), "Empty extremes");
        Reject([&] { list.SeeNext(); });
        Reject([&] { list.SeeAt(0); });
        list.Reverse(); list.RemoveAll();
        list.AddItem(Make("M00000003"));
        Check(list.SeeNext()->GetM_Number() == "M00000003", "Single traversal");
        Check(!list.SeeNext() && !list.SeeNext(), "Past end");
        list.AddItem(Make("M00000001"));
        list.AddItem(Make("M00000002"));
        Check(list.SeeNext()->GetM_Number() == "M00000001", "Sorted head");
        Check(list.SeeNext()->GetM_Number() == "M00000002", "Sorted middle");
        Check(list.SeeNext()->GetM_Number() == "M00000003", "Sorted tail");
        Check(!list.SeeNext(), "Traversal end");
        list.Reset();
        Check(list.SeeNext()->GetM_Number() == "M00000001", "Reset");
        list.SeeAt(1);
        Check(list.SeeNext()->GetM_Number() == "M00000003", "SeeAt cursor");
        Reject([&] { list.SeeAt(-1); });
        Reject([&] { list.SeeAt(3); });
        std::cout << "PASS: sorting, empty/single lists, SeeNext, SeeAt and Reset\n";

        list.Reset();
        List copy(list);
        Check(copy.SeeNext() != list.SeeNext(), "Deep copied students");
        Student middle("M00000002");
        delete list.GetItem(&middle);
        Check(list.SeeNext()->GetM_Number() == "M00000003", "Removed cursor");
        Check(copy.Size() == 3 && list.Size() == 2, "Independent copy");
        List assigned;
        assigned.AddItem(Make("M00000009"));
        assigned = copy;
        assigned = assigned;
        Check(assigned.Size() == 3 && assigned.IsInList(&middle), "Assignment");
        list = List{};
        Check(list.IsEmpty(), "Empty assignment");
        Student first("M00000001"), last("M00000003");
        delete assigned.GetItem(&first);
        delete assigned.GetItem(&last);
        delete assigned.GetItem(&middle);
        Check(assigned.IsEmpty() && !assigned.GetItem(&middle), "Remove head, tail, only");
        std::cout << "PASS: removal, independent copies, assignment and self-assignment\n";

        copy.Reverse();
        Check(copy.SeeAt(0)->GetM_Number() == "M00000003", "Reverse");
        copy.AddItem(Make("M00000004"));
        Check(copy.SeeAt(0)->GetM_Number() == "M00000004", "Reversed insertion");
        Check(copy.GetLargest()->GetM_Number() == "M00000004", "Largest reversed");
        Check(copy.GetSmallest()->GetM_Number() == "M00000001", "Smallest reversed");
        copy.Reverse();
        copy.Reset();
        std::ostringstream display;
        auto previous = std::cout.rdbuf(display.rdbuf());
        copy.DisplayAll();
        std::cout.rdbuf(previous);
        Check(copy.SeeNext()->GetM_Number() == "M00000001", "Display cursor");
        Check(display.str().find("M00000004") != std::string::npos, "Display contents");
        std::cout << "PASS: Reverse, extremes, DisplayAll and cursor preservation\n";

        const auto folder = std::filesystem::temp_directory_path() / "miniproject1-tests";
        std::filesystem::create_directories(folder);
        const std::string file = (folder / "students.txt").string();
        Check(copy.SaveToFile(file), "Save students");
        Check(list.LoadFromFile(file) && list.Size() == 4, "Load students");
        Check(list.SeeNext()->GetM_Number() == "M00000001", "Load sorted");
        Check(!list.LoadFromFile((folder / "missing" / "file.txt").string()), "Missing file");
        Check(!list.SaveToFile((folder / "missing" / "file.txt").string()), "Unwritable path");
        { std::ofstream bad(file); bad << "broken record\n"; }
        Check(!list.LoadFromFile(file) && list.Size() == 4, "Bad file preserves data");
        { std::ofstream bad(file); bad << *copy.GetSmallest() << '\n' << *copy.GetSmallest() << '\n'; }
        Check(!list.LoadFromFile(file) && list.Size() == 4, "Duplicate file rejected");
        assigned.RemoveAll();
        Check(assigned.SaveToFile(file) && list.LoadFromFile(file) && list.IsEmpty(), "Empty file");
        std::filesystem::remove(file);
        std::cout << "PASS: save/load, empty file, missing file, corrupt/duplicate records\n";

        Reject([] { Student s("", "Name", "M00000001", 2000, 1, 1); });
        Reject([] { Student s("Name", "  ", "M00000001", 2000, 1, 1); });
        Reject([] { Student s("m00000001"); });
        Reject([] { Student s("M123"); });
        Reject([] { Student s("M0000000x"); });
        for (double grade : {-0.1, 4.1, std::numeric_limits<double>::quiet_NaN()})
            Reject([&] { Student s("A", "B", "M00000001", 2000, 1, 1, grade); });
        Reject([] { Student s("A", "B", "M00000001", 1900, 2, 29); });
        Reject([] { Student s("A", "B", "M00000001", 2000, 13, 1); });
        Reject([] { Student s("A", "B", "M00000001", 2000, 4, 31); });
        Reject([] { Student s("A", "B", "M00000001", 9999, 1, 1); });
        Student student("Mary Jane", "Smith", "M00000001", 2000, 2, 29);
        Check(student.getGPA() == 0 && student.getName() == "Mary Jane Smith", "Default GPA/name");
        std::stringstream record;
        record << student;
        Student restored;
        record >> restored;
        Check(restored.getName() == student.getName() && restored == student, "Quoted names");
        auto duplicate = std::make_unique<Student>(student);
        Reject([&] { copy.AddItem(duplicate.get()); });
        std::cout << "PASS: names, M Numbers, GPA, birthdays, duplicates and serialization\n";

        {
            DoubleyLinkedList<Tracked> tracked;
            tracked.AddItem(new Tracked(2));
            tracked.AddItem(new Tracked(1));
            DoubleyLinkedList<Tracked> second(tracked), third;
            third.AddItem(new Tracked(9));
            third = second;
            third = third;
            Tracked key(1);
            delete tracked.GetItem(&key);
            second.RemoveAll();
            tracked.Reverse();
        }
        Check(Tracked::alive == 0, "All owned objects released");
        std::cout << "PASS: generic items and object lifetime accounting\nAll tests passed.\n";
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}
