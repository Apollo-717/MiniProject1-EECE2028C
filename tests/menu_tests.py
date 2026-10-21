import pathlib
import subprocess
import sys
import tempfile

exe = str(pathlib.Path(sys.argv[1]).resolve())

def run(lines):
    result = subprocess.run([exe], input='\n'.join(lines) + '\n', text=True,
                            capture_output=True, timeout=10)
    assert result.returncode == 0, result.stderr
    return result.stdout

with tempfile.TemporaryDirectory() as directory:
    saved = str(pathlib.Path(directory) / 'students.txt')
    empty = str(pathlib.Path(directory) / 'empty.txt')
    output = run(['7', empty,
                  '1', 'Grace', 'Hopper', 'M00000003', '4', '1906', '12', '9',
                  '1', 'Ada', 'Lovelace', 'M00000001', '', '1815', '12', '10',
                  '4', '7', saved, '12'])
    assert output.count('Students saved.') == 2
    assert 'GPA : 0.00' in output
    restart = run(['8', saved, '4', '14', '12'])
    assert 'Students loaded.' in restart and 'Size: 2' in restart
    assert restart.index('M00000001') < restart.index('M00000003')
    duplicate = run(['8', saved, '1', 'Ada', 'Lovelace', 'M00000001', '14', '12'])
    assert 'already exists' in duplicate and 'Size: 2' in duplicate
    invalid = run(['1', 'Test', 'Student', 'M00000002', '5', '2000', '1', '1',
                   '8', str(pathlib.Path(directory) / 'missing.txt'), 'oops', '12'])
    assert 'GPA must be between' in invalid
    assert 'Unable to open file' in invalid
    assert 'Please enter a valid number' in invalid
    assert 'Goodbye.' in invalid
    assert run([]).endswith('Choice: ')
    pathlib.Path('build/menu-output.txt').write_text(output + restart + duplicate + invalid)
    print('PASS: empty save, optional GPA, save, exit, restart and sorted reload')
    print('PASS: duplicate rejection, invalid GPA, missing file, bad menu input and EOF')
