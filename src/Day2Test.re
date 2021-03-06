Jest.test("part 1", () => {
  let input = [
    "abcdef",
    "bababc",
    "abbcde",
    "abcccd",
    "aabcdd",
    "abcdee",
    "ababab",
  ];
  Day2.part1(input)->Jest.expect->Jest.Expect.toBe(12);
  Js.undefined;
});

Jest.test("part 2", () => {
  let input = ["abcde", "fghij", "klmno", "pqrst", "fguij", "axcye", "wvxyz"];
  Day2.part2(input)->Jest.expect->Jest.Expect.toBe("fgij");
  Js.undefined;
});
