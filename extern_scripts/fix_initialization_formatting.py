import os
import re

def convert_initialization(file_path):
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()

    # Regular expression to find and replace variable initializations
    # Matches lines that start with a type followed by a variable name and initialization
    pattern = re.compile(r'(\b(?:int|float|double|char|bool|short|long|unsigned|signed|auto)\b\s+\w+)\s*=\s*(.+?);')
    new_content = pattern.sub(r'\1{\2};', content)

    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(new_content)

def process_directory(directory):
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith('.cpp') or file.endswith('.h'):
                file_path = os.path.join(root, file)
                convert_initialization(file_path)

# Replace 'your_project_directory' with the path to your project
process_directory('lib')
process_directory('src')
