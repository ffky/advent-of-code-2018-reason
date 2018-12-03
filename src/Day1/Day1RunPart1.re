let inputPath = Node.Process.argv->Belt.Array.getExn(2);
let data = Node.Fs.readFileAsUtf8Sync(inputPath);
Day1.parse(data)->Day1.part1->Js.log;
