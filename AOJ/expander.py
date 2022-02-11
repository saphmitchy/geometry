#!/usr/bin/env python3

import argparse
from cmath import exp
from typing import List
import re

include_file = re.compile("(?<=#include\s\")(src/|)[a-z_]+?(|.hpp)(?=\")")
include_guard = re.compile("GEOMETRY_")
SOURCE_PATH = "../src/"

expand = set()

def dfs(inputFile : str) -> List[str]:
    ret = []
    with open(inputFile) as f:
        lines = f.readlines()

    for line in lines:
        if include_guard.search(line):
            continue
        if include_file.search(line):
            filePath = include_file.search(line).group(0)
            if filePath[:4] == "src/":
                filePath = filePath[4:]
            if filePath in expand:
                continue
            expand.add(filePath)
            ret = ret + dfs(SOURCE_PATH + filePath)
        else:
            ret.append(line)
    return ret

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="indlude expander")
    parser.add_argument("input", nargs=1, type=str)
    parser.add_argument("--output", nargs=1, default="output.cpp", type=str)
    
    args = parser.parse_args()
    lines = dfs(args.input[0])

    with open(args.output, 'w') as f:
        for i in lines:
            f.write(i)