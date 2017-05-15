while True:
    print("Height:", end="")
    h = int(input())
    
    if h > 0 or h < 23:
        break
    
for i in range(h):
    print(" " * (h-i), end="")
    print("#" * (i+1), end="")
    print("  ", end="")
    print("#" * (i+1), end="")
    print(" " * (h-i), end="")
    print()
    