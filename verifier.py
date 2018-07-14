import string

exclude = set(string.punctuation)

dict = {}
words = 0;
with open('ATaleOfTwoCities.txt','r') as f:
    for line in f:
        for word in line.split():
            word = ''.join(ch for ch in word if ch not in exclude)
            word = (word.strip()).lower()
            words+=1
            try:
                dict[word] += 1
            except KeyError:
                dict[word] = 1
print "total words: " + str(words)
print "total uniques: " + str(len(dict))
