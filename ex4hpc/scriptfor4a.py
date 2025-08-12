import os
import random
import string

file_sizes = [1024, 1024 * 1024, 1024 * 1024 * 1024]
for file_size in file_sizes:
    file_path = f'random_data_file_{file_size}.bin'

    with open(file_path, 'wb') as f:
        while os.path.getsize(file_path) < file_size:
            random_data = ''.join(random.choices(string.ascii_letters, k=1024)).encode('utf-8')
            f.write(random_data)
    print("File Made ", file_path)
