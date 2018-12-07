let dirname = [%bs.node __dirname];
let dirname = Belt.Option.getExn(dirname);
let input = Node.Fs.readFileAsUtf8Sync(dirname ++ "/Day5Input")->Day5.parse;
Day5.part1(input)->Js.log;
Day5.part2(input)->Js.log;
