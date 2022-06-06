#!/usr/bin/env python3

import argparse, re, os
from typing import List

# regular experssion to recognize include files
include_file = re.compile('(?<=#include\s\")[a-z_]+?(|.hpp)(?=\")')
# regular experssion to recognize include guard
include_guard = re.compile('GEOMETRY_')

# directory where this file locates
DIR_PATH = os.path.dirname(__file__)
# geometry libarary source path
SOURCE_PATH = os.path.join(DIR_PATH, '../src/')

def comment_remover(line : str) -> str:
    '''
    Reomve comments.  If all of the line is removed, returns \\n.
    Else returns lines that comments removed.
    '''
    if '/*' in line or \
       '*/' in line or \
        re.match('^//.*', line) or \
        re.match('^ *\* .*', line):
        return "\n"
    else:
        return  re.sub(r'(.*?) *//(.*)', r'\1', line)

expandedFile = set() # store expaneded files

def dfs(inputFile : str, remain_comment : bool) -> List[str]:
    '''
    Expand include files with DFS
    remain_comment is the flag which determine if comments are removed.
    '''
    ret = [] # store expaneded string

    # get file string.
    with open(inputFile) as f:
        lines = f.readlines()

    for line in lines:
        # If the line is include guard or empty line, it's passed.
        if include_guard.search(line) or line == "\n":
            continue
        # if the line is include directive
        if include_file.search(line):
            # get file name
            filePath = include_file.search(line).group(0)
            # Prefix src/ is removed. This might be needless.
            if filePath[:4] == "src/":
                filePath = filePath[4:]
            # If the file has not been expaned yet, it's expaneded.
            if filePath not in expandedFile:
                expandedFile.add(filePath)
                ret = ret + dfs(os.path.join(SOURCE_PATH, filePath),
                                remain_comment)
        else:
            if remain_comment:
                ret.append(line)
            else:
                # get removed line
                removed = comment_remover(line)
                # If only newline is remain, the line is ignored.
                if removed != "\n":
                    ret.append(removed)
    return ret

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='indlude expander')
    #define input file argumant
    parser.add_argument('input',
                        nargs=1,
                        type=str)
    #define output file argumant
    parser.add_argument('--output',
                        nargs=1,
                        default= os.path.join(DIR_PATH, 'output.cpp'),
                        type=str)
    #define comment argumant
    parser.add_argument('--remain_comment',
                        action='store_true')

    # recieve arguemnt
    args = parser.parse_args()
    # start parse
    lines = dfs(args.input[0], args.remain_comment)

    # output results
    with open(args.output, 'w') as f:
        for i in lines:
            f.write(i)