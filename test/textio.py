# all hand written
from typing import Any


from pathlib import Path
import subprocess


def main() -> None:
	# get the textout file
	# this is relitive to were its being run from not were the file actually is
	textout = Path("./test/tests.txt")
	tests: list[dict[str, str]] = []
	with open(textout, "r") as file:
		lines = file.readlines()
		# we just want the output lines
		x: int = 0
		j: int = 0
		for i in lines:
			if x % 2 != 0:
				tests[j]["output"] = i
				j += 1
			else:
				tests.append({})
				tests[j]["input"] = i

			x += 1
		inputs = [tests[x]["input"] for x in range(0, len(tests))]
		inputs[len(inputs) - 1] = inputs[len(inputs) - 1].strip()
		output = [tests[x]["output"] for x in range(0, len(tests))]

		with Path("./test/input.txt").open("w+") as input_file:
			input_file.writelines(inputs)
		with Path("./test/correctout.txt").open("w+") as output_file:
			output_file.writelines(output)

		with (
			Path("./test/textout.txt").open("w+") as textout,
			Path("./test/input.txt").open("r") as input_file,
		):
			test = subprocess.run(
				[str(Path("build/out").absolute())],
				stdin=input_file,
				stdout=textout,
			)
	textout = Path("./test/textout.txt")
	with textout.open("r") as file:
		lines = file.readlines()
		# we just want the output lines
		output: list[str] = []
		x = 0
		for i in lines:
			if x % 2 != 0:
				output.append(i)
			x += 1
		with Path("./test/onlyout.txt").open("w+") as f:
			f.writelines(output)
	diff = subprocess.run(
		[
			"diff",
			str(Path("./test/correctout.txt").absolute()),
			str(Path("./test/onlyout.txt").absolute()),
		],
		capture_output=True,
	)
	if diff.stdout == b"":
		print("Tests pass!")
	else:
		print(str(diff.stdout).replace("\\n", "\n").strip("b").strip("'"))


if __name__ == "__main__":
	main()
