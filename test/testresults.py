# all hand written
from pathlib import Path


def main() -> None:
	# get results file
	textout = Path("./test/result.txt")
	with open(textout, "r") as file:
		result = file.read()
		if len(result) == 0:
			print("All tests passed!")
		else:
			# just print the diff
			print("Tests failed!")
			print(result)


if __name__ == "__main__":
	main()
