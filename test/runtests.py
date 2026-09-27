# all hand written
from typing import Any


from pathlib import Path
import subprocess


def main() -> None:
	# get the textout file
	# this is relitive to were its being run from not were the file actually is
	textout = Path("./test/tests.txt")
	tests: list[dict[str, str]] = []
	with textout.open("r") as file:
		lines = file.readlines()
		x: int = 0
		j: int = 0
		# create a list of tests, each one has an input and an output
		for i in lines:
			# is this even, basiclly output is lines 1 3 5 7 ect.
			if x % 2 != 0:
				tests[j]["output"] = i
				j += 1
			else:
				# append to prevent out of bound error
				tests.append({})
				tests[j]["input"] = i

			x += 1
	failed_tests = 0
	for test in tests:
		testrun = subprocess.run(
			[str(Path("build/out").absolute())],
			input=test["input"] + "END",
			capture_output=True,
			text=True,
		)
		result = testrun.stdout.splitlines(keepends=True)[1]
		if result == test["output"]:
			continue
		else:
			print("Test failed!")
			print("Test input: " + test["input"])
			print("Expected output: " + test["output"])
			print("Actual output: " + result)
			failed_tests += 1
	if failed_tests == 0:
		print("All tests passed!")
	else:
		print(str(failed_tests) + " tests failed")


if __name__ == "__main__":
	main()
