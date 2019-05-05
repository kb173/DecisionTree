capitals = [0, 0]
total = [0, 0]
numbers = [0, 0]
periods = [0, 0]
allcaps = [0, 0]
urls = [0, 0]
smileys = [0, 0]
congrats = [0, 0]
free = [0, 0]
allcapswords = [0, 0]

lines = []


with open("Datasets/spam.csv", encoding="latin-1") as datafile:
	for line in datafile:
		lines.append(line)

		class_data = line.split(",")
		
		classification = class_data[0]
		line = class_data[1]

		if classification == "ham":
			index = 0
		else:
			index = 1

		total[index] += 1
		capitals[index] += sum(c.isupper() for c in line)
		numbers[index] += sum(c.isdigit() for c in line)
		periods[index] += sum(c == "." for c in line)

		if line.isupper():
			allcaps[index] += 1

		if "http" in line or "www" in line:
			urls[index] += 1

		if ":)" in line or ":-)" in line:
			smileys[index] += 1

		if "congrats" in line.lower() or "congratulations" in line.lower() or "congratz" in line.lower():
			congrats[index] += 1

		if "free" in line.lower():
			free[index] += 1

		for word in line.split():
			if word.isupper():
				allcapswords[index] += 1

print("Avg capitals in ham: {}".format(capitals[0] / total[0]))
print("Avg capitals in spam: {}".format(capitals[1] / total[1]))
print()
print("Avg digits in ham: {}".format(numbers[0] / total[0]))
print("Avg digits in spam: {}".format(numbers[1] / total[1]))
print()
print("Avg periods in ham: {}".format(periods[0] / total[0]))
print("Avg periods in spam: {}".format(periods[1] / total[1]))
print()
print("Percentage lines with all caps in ham: {}".format(allcaps[0] / total[0]))
print("Percentage lines with all caps in spam: {}".format(allcaps[1] / total[1]))
print()
print("Percentage lines with url in ham: {}".format(urls[0] / total[0]))
print("Percentage lines with url in spam: {}".format(urls[1] / total[1]))
print()
print("Percentage lines with smiley in ham: {}".format(smileys[0] / total[0]))
print("Percentage lines with smiley in spam: {}".format(smileys[1] / total[1]))
print()
print("Percentage lines with congrats in ham: {}".format(congrats[0] / total[0]))
print("Percentage lines with congrats in spam: {}".format(congrats[1] / total[1]))
print()
print("Percentage lines with free in ham: {}".format(free[0] / total[0]))
print("Percentage lines with free in spam: {}".format(free[1] / total[1]))
print()
print("Percentage words in caps in ham: {}".format(allcapswords[0] / total[0]))
print("Percentage words in caps spam: {}".format(allcapswords[1] / total[1]))

# Therefore columns:
# Digits: 0, 1-4, 5-10, >10
# All caps line?
# URL in line?
# Smiley in line?
# Congrats in line?
# Free in line?
# Capswords 0, 1, >1

newheader = "digits,allcaps,url,smiley,congrats,free,capswords,spam"

with open("Datasets/spam_char.csv", "w+") as outfile:
	outfile.write(newheader + "\n")

	for line in lines:
		class_data = line.split(",", 1)
		
		classification = class_data[0]
		line = class_data[1]

		digits = sum(c.isdigit() for c in line)
		if digits == 0:
			digits = "0"
		elif digits > 1 and digits < 5:
			digits = "1-4"
		elif digits > 4 and digits < 11:
			digits = "5-10"
		else:
			digits = ">10"
		
		allcaps = "no"
		if line.isupper():
			allcaps = "yes"

		url = "no"
		if "http" in line or "www" in line:
			url = "yes"

		smiley = "no"
		if ":)" in line or ":-)" in line:
			smiley = "yes"

		congrats = "no"
		if "congrats" in line.lower() or "congratulations" in line.lower() or "congratz" in line.lower():
			congrats = "yes"

		free = "no"
		if "free" in line.lower():
			free = "yes"

		capswords = 0
		for word in line.split():
			if word.isupper():
				capswords += 1
		if capswords > 1:
			capswords = ">1"
		else:
			capswords = str(capswords)

		if classification == "ham":
			spam = "no"
		else:
			spam = "yes"

		outfile.write(digits + "," + allcaps + "," + url + "," + smiley + "," + congrats + "," + free + "," + capswords + "," + spam + "\n")
