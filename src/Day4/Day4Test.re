let input = [|
  ("1518-11-01 00:00", Day4.BeginsShift(10)),
  ("1518-11-01 00:05", FallsAsleep),
  ("1518-11-01 00:25", WakesUp),
  ("1518-11-01 00:30", FallsAsleep),
  ("1518-11-01 00:55", WakesUp),
  ("1518-11-01 23:58", BeginsShift(99)),
  ("1518-11-02 00:40", FallsAsleep),
  ("1518-11-02 00:50", WakesUp),
  ("1518-11-03 00:05", BeginsShift(10)),
  ("1518-11-03 00:24", FallsAsleep),
  ("1518-11-03 00:29", WakesUp),
  ("1518-11-04 00:02", BeginsShift(99)),
  ("1518-11-04 00:36", FallsAsleep),
  ("1518-11-04 00:46", WakesUp),
  ("1518-11-05 00:03", BeginsShift(99)),
  ("1518-11-05 00:45", FallsAsleep),
  ("1518-11-05 00:55", WakesUp),
|];

Jest.test("parses input", () => {
  let raw = {|[1518-11-01 00:00] Guard #10 begins shift
[1518-11-01 00:05] falls asleep
[1518-11-01 00:25] wakes up
[1518-11-01 00:30] falls asleep
[1518-11-01 00:55] wakes up
[1518-11-01 23:58] Guard #99 begins shift
[1518-11-02 00:40] falls asleep
[1518-11-02 00:50] wakes up
[1518-11-03 00:05] Guard #10 begins shift
[1518-11-03 00:24] falls asleep
[1518-11-03 00:29] wakes up
[1518-11-04 00:02] Guard #99 begins shift
[1518-11-04 00:36] falls asleep
[1518-11-04 00:46] wakes up
[1518-11-05 00:03] Guard #99 begins shift
[1518-11-05 00:45] falls asleep
[1518-11-05 00:55] wakes up
|};

  Day4.parse(raw)->Jest.expect->Jest.Expect.toEqual(input);
  Js.undefined;
});

Jest.test("sort input", () => {
  let input = [|
    ("1518-11-01 00:25", Day4.WakesUp),
    ("1518-11-01 00:05", FallsAsleep),
    ("1518-11-01 00:00", BeginsShift(10)),
    ("1518-11-01 00:30", FallsAsleep),
  |];

  Day4.sortInput(input)
  ->Jest.expect
  ->Jest.Expect.toEqual([|
      ("1518-11-01 00:00", Day4.BeginsShift(10)),
      ("1518-11-01 00:05", FallsAsleep),
      ("1518-11-01 00:25", WakesUp),
      ("1518-11-01 00:30", FallsAsleep),
    |]);

  Js.undefined;
});

Jest.test("part 1", () => {
  Day4.part1(input)->Jest.expect->Jest.Expect.toBe(240);
  Js.undefined;
});

Jest.test("part 2", () => {
  Day4.part2(input)->Jest.expect->Jest.Expect.toBe(4455);
  Js.undefined;
});
