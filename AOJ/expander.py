#!/usr/bin/env python3

import argparse, re, os
from typing import List

include_file = re.compile('(?<=#include\s\")[a-z_]+?(|.hpp)(?=\")')
include_guard = re.compile('GEOMETRY_')
DIR_PATH = os.path.dirname(__file__)
SOURCE_PATH = os.path.join(DIR_PATH, '../src/')

'''
コメントアウトを削除する。
すべて削除する場合はNone を返し、
それ以外は削除後の文字列を返す
'''
def comment_remover(line : str) -> str:
    if '/*' in line or \
       '*/' in line or \
        re.match('^//.*', line) or \
        re.match('^ \* .*', line):
        return "\n"
    else:
        return  re.sub(r'(.*?) *//(.*)', r'\1', line)

expand = set()
def dfs(inputFile : str, remain_comment : bool) -> List[str]:
    ret = []
    with open(inputFile) as f:
        lines = f.readlines()

    for line in lines:
        if include_guard.search(line) or line == "\n":
            continue
        if include_file.search(line):
            filePath = include_file.search(line).group(0)
            if filePath[:4] == "src/":
                filePath = filePath[4:]
            if filePath in expand:
                continue
            expand.add(filePath)
            ret = ret + dfs(os.path.join(SOURCE_PATH, filePath), remain_comment)
        else:
            if remain_comment:
                ret.append(line)
            else:
                removed = comment_remover(line)
                if removed != "\n":
                    ret.append(removed)
    return ret

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='indlude expander')
    parser.add_argument('input', nargs=1, type=str)
    parser.add_argument('--output', nargs=1, default= os.path.join(DIR_PATH, 'output.cpp'), type=str)
    parser.add_argument('--remain_comment', action='store_true')

    args = parser.parse_args()
    lines = dfs(args.input[0], args.remain_comment)

    with open(args.output, 'w') as f:
        for i in lines:
            f.write(i)