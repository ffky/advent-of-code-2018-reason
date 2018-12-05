let inputPath = Node.Process.argv->Belt.Array.getExn(2);
let data = Node.Fs.readFileAsUtf8Sync(inputPath);
Day4.parse(data)->Day4.part1->Js.log;
