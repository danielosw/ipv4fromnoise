# all hand written
from pathlib import Path


def main() -> None:
	# get the textout file
	# this is relitive to were its being run from not were the file actually is
	textout = Path("./test/textout.txt")
	with open(textout, "r") as file:
		lines = file.readlines()
		# we just want the output lines
		output = []
		x = 0
		for i in lines:
			if x % 2 != 0:
				output.append(i)
			x += 1
		with open(Path("./test/onlyout.txt"), "w+") as f:
			f.writelines(output)


if __name__ == "__main__":
	main()
