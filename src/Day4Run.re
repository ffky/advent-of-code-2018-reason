let dirname = [%bs.node __dirname];
let dirname = Belt.Option.getExn(dirname);
let input = Node.Fs.readFileAsUtf8Sync(dirname ++ "/Day4Input")->Day4.parse;
Day4.part1(input)->Js.log;
Day4.part2(input)->Js.log;
