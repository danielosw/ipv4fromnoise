# all hand written
from typing import Any


from pathlib import Path


def main() -> None:
	# get the textout file
	# this is relitive to were its being run from not were the file actually is
	textout = Path("./test/tests.txt")
	with open(textout, "r") as file:
		lines = file.readlines()
		# we just want the output lines
		output: list[str] = []
		inputs: list[str] = []
		x = 0
		for i in lines:
			if x % 2 != 0:
				output.append(i)
			else:
				inputs.append(i)
			x += 1
		with open(Path("./test/input.txt"), "w+") as f:
			inputs[len(inputs) - 1] = inputs[len(inputs) - 1].strip()

			f.writelines(inputs)
		with open(Path("./test/correctout.txt"), "w+") as f:
			# we need to strip the \n off the last one or it beaks
			f.writelines(output)


if __name__ == "__main__":
	main()
