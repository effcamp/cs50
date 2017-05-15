import sys

# error checking
if len(sys.argv) != 2 or int(sys.argv[1]) == 0:
    print("Please enter a valid key")
    exit(1)

# get message from user and store it in 'key'
message = input("Plaintext: ")
key = int(sys.argv[1])

print("Ciphertext: ",end="")

# iterate through each character in the string given by the user
# does the math to shift each letter by the key
for c in message:
    if c.islower():
        print("{}".format(chr(((ord(c) - 97 + key) % 26 + 97))),end="")
        
    elif c.isupper():
        print("{}".format(chr(((ord(c) - 65 + key) % 26 + 65))),end="")
        
    else:
       print(c,end="")

print()
exit(0)