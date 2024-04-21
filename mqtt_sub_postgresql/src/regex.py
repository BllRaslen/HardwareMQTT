import os
import re
import subprocess


class JavaClass:
    def __init__(self, filename, javadoc_lines, other_comments_lines, code_lines, loc, function_count,
                 comment_deviation):
        self.filename = filename
        self.javadoc_lines = javadoc_lines
        self.other_comments_lines = other_comments_lines
        self.code_lines = code_lines
        self.loc = loc
        self.function_count = function_count
        self.comment_deviation = comment_deviation


def analyze_java_class(filename, file_content):
    javadoc_pattern = re.compile(r'/\*\*.*?\*/', re.DOTALL)
    single_line_comment_pattern = re.compile(r'//.*')
    multiline_comment_pattern = re.compile(r'/\*.*?\*/', re.DOTALL)
    function_pattern = re.compile(
        r'\b(?:public|private|protected|static|final|\s) +[\w<>\[\]]+\s+(\w+) *\([^\)]*\) *(\{?|[^;])')

    javadoc_lines = len(re.findall(javadoc_pattern, file_content))
    single_line_comments = len(re.findall(single_line_comment_pattern, file_content))
    multiline_comments = len(re.findall(multiline_comment_pattern, file_content))
    other_comments_lines = single_line_comments + multiline_comments

    code_lines = len(file_content.split('\n')) - other_comments_lines
    loc = len(file_content.split('\n'))
    function_count = len(re.findall(function_pattern, file_content))

    YG = ((javadoc_lines + other_comments_lines) * 0.8) / function_count if function_count != 0 else 0
    YH = (code_lines / function_count) * 0.3 if function_count != 0 else 0

    comment_deviation = ((100 * YG) / YH) - 100 if YH != 0 else -100

    return JavaClass(filename, javadoc_lines, other_comments_lines, code_lines, loc, function_count, comment_deviation)


def main():
    repo_url = input("Please enter the GitHub repository URL: ")
    clone_command = ['git', 'clone', repo_url]

    try:
        subprocess.run(clone_command, check=True)
    except subprocess.CalledProcessError as e:
        print("Error:", e)
        return

    directory_name = repo_url.split('/')[-1].split('.')[0]
    java_files = [file for file in os.listdir(directory_name) if file.endswith('.java')]

    for filename in java_files:
        with open(os.path.join(directory_name, filename), 'r', encoding='utf-8') as file:
            file_content = file.read()
            java_class = analyze_java_class(filename, file_content)
            print(f"Sınıf: {java_class.filename}")
            print(f"Javadoc Satır Sayısı: {java_class.javadoc_lines}")
            print(f"Yorum Satır Sayısı: {java_class.other_comments_lines}")
            print(f"Kod Satır Sayısı: {java_class.code_lines}")
            print(f"LOC: {java_class.loc}")
            print(f"Fonksiyon Sayısı: {java_class.function_count}")
            print(f"Yorum Sapma Yüzdesi: %{java_class.comment_deviation:.2f}")
            print("-----------------------------------------")


if __name__ == "__main__":
    main()
