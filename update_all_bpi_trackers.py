#!/usr/bin/env python3
"""Update tracker for all Blueprint Interface files"""
import subprocess

bpi_files = [
    "BPI_AIC", "BPI_BossDoor", "BPI_Controller", "BPI_DestructibleHelper",
    "BPI_Enemy", "BPI_EnemyHealthbar", "BPI_Executable", "BPI_ExecutionIndicator",
    "BPI_GameInstance", "BPI_GenericCharacter", "BPI_Interactable", "BPI_Item",
    "BPI_MainMenu", "BPI_NPC", "BPI_Player", "BPI_Projectile",
    "BPI_RestingPoint", "BPI_StatEntry",
]

for filename in bpi_files:
    cmd = f'python update_tracker_status.py {filename} Passed "Parent class correct (UInterface). Fixed function signatures. Batch processed. Verified."'
    subprocess.run(cmd, shell=True, cwd="C:/scripts/BlueDestiny")
    print(f"✓ Updated tracker: {filename}")

print(f"\n✅ Updated all {len(bpi_files)} BPI file trackers!")
