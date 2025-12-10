#!/usr/bin/env python3
# https://github.com/hughcoleman/advent-of-code/blob/main/2025/10.py

import itertools as it
import sys
import z3

part2 = 0
for machine in iter(sys.stdin.readline, ""):
    pattern, *buttons, joltages = machine.split()

    pattern = pattern[1:-1]
    buttons = [
        set(map(int, button[1:-1].split(',')))
            for button in buttons
    ]
    joltages = list(map(int, joltages[1:-1].split(',')))

    presses = [
        z3.Int(f"press{i}") for i in range(len(buttons))
    ]

    s = z3.Optimize()
    s.add(z3.And([press >= 0 for press in presses]))
    s.add(z3.And([
        sum(presses[j] for j, button in enumerate(buttons) if i in button) == joltage
            for i, joltage in enumerate(joltages)
    ]))
    s.minimize(sum(presses))
    assert s.check() == z3.sat

    m = s.model()
    for press in presses:
        part2 = part2 + m[press].as_long()

print(part2)
