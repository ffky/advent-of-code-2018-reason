let inputPath = Process.argv->Belt.Array.getExn(2);

let data =
  Fs.readFileSync(inputPath, Fs.ReadFile.Options.t(~encoding="utf-8"));

Day2.parse(data)->Day2.part2->Js.log;
