import sys

# check for correct number of cmd line arguments
if len(sys.argv) != 2:
    print("Please enter a valid key")
    exit(1)
    
# check key for any forbidden characters
for c in sys.argv[1]:
    if c.isalpha() == False:
        print("Please enter a valid key!")
        exit(1)
      
# make a list and convert the user input to numbers from 0 - 25
key = [] 
for i in sys.argv[1].upper():
    key.append(ord(i) - 65)

mod = len(sys.argv[1])

# get message from the user
message = input("Plaintext: ")
k = 0

#for each letter, modify it using the key
print("Ciphertext: ",end="")

for c in message:
    if c.islower():
        print("{}".format(chr((ord(c) - 97 + key[k % mod]) % 26 + 97)),end="")
        k += 1
    elif c.isupper():
        print("{}".format(chr((ord(c) - 65 + key[k % mod]) % 26 + 65)),end="")
        k += 1
    else:
        print(c,end="")

print()
    
        