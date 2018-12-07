open Belt;

type log =
  | BeginsShift(int)
  | WakesUp
  | FallsAsleep;

let parse = input => {
  let get = (matches, index) => matches->Array.getExn(index);
  Js.String.split("\n", input)
  ->Array.keep(x => x != "")
  ->Array.map(log => {
      let matches =
        log->Js.String.match([%re "/\\[(.*)\\] (.*)/"], _)->Option.getExn;
      let date = matches->get(1);
      let log =
        switch (matches->get(2)) {
        | "falls asleep" => FallsAsleep
        | "wakes up" => WakesUp
        | text =>
          let matches =
            text
            ->Js.String.match([%re "/Guard #(\\d*) begins shift/"], _)
            ->Option.getExn;
          let guardNum = matches->get(1)->int_of_string;
          BeginsShift(guardNum);
        };
      (date, log);
    });
};

let sortInput = input =>
  SortArray.stableSortBy(input, ((a, _), (b, _)) =>
    DateFns.compareStr(a, b)
  );

/* Up to but not including end */
let rec updateMap = (map, guardId, start, end_) =>
  if (start >= end_) {
    map;
  } else {
    let updated =
      switch (map->Map.Int.get(guardId)) {
      | None =>
        map->Map.Int.set(guardId, Map.Int.empty->Map.Int.set(start, 1))
      | Some(minuteMap) =>
        switch (minuteMap->Map.Int.get(start)) {
        | None => map->Map.Int.set(guardId, minuteMap->Map.Int.set(start, 1))
        | Some(count) =>
          map->Map.Int.set(guardId, minuteMap->Map.Int.set(start, count + 1))
        }
      };
    updateMap(updated, guardId, start + 1, end_);
  };

/* Assume they always wake up at some point of their shift */
let process = l => {
  let rec aux = (l, minuteCountMap, prev, guardId) =>
    switch (l) {
    | [] => minuteCountMap
    | [h, ...t] =>
      let (date, log) = h;
      switch (log) {
      | WakesUp =>
        /* first can't be WakesUp */
        let (prevDate, prevLog) = prev->Option.getExn;
        switch (prevLog) {
        | WakesUp
        | BeginsShift(_) =>
          Js.Exn.raiseError("prev log should be falls asleep")
        | FallsAsleep =>
          switch (guardId) {
          | None => aux(t, minuteCountMap, Some(h), None)
          | Some(guardId) =>
            let prevMin = DateFns.getMinutesStr(prevDate);
            let nowMin = DateFns.getMinutesStr(date);
            let updated = updateMap(minuteCountMap, guardId, prevMin, nowMin);
            aux(t, updated, Some(h), Some(guardId));
          }
        };
      | FallsAsleep =>
        /* pretty sure we do nothing here except pass it along */
        aux(t, minuteCountMap, Some(h), guardId)
      | BeginsShift(guardId) =>
        switch (prev) {
        | None => aux(t, minuteCountMap, Some(h), Some(guardId))
        | Some(prev) =>
          let (_prevDate, prevLog) = prev;
          switch (prevLog) {
          | FallsAsleep =>
            Js.Exn.raiseError("previous guard didn't wake up lol")
          | WakesUp
          | BeginsShift(_) => aux(t, minuteCountMap, Some(h), Some(guardId))
          };
        }
      };
    };
  aux(l, Map.Int.empty, None, None);
};

let maxMinAsleepGuardId = map => {
  let guardTotalMap =
    map->Map.Int.reduce(
      Map.Int.empty,
      (guardTotalMap, guardId, minuteMap) => {
        let total =
          minuteMap->Map.Int.reduce(0, (acc, _minute, count) => acc + count);
        guardTotalMap->Map.Int.set(guardId, total);
      },
    );
  guardTotalMap->Map.Int.reduce(None, (acc, guardId, total) =>
    switch (acc) {
    | None => Some((guardId, total))
    | Some((guardId2, total2)) =>
      total > total2 ? Some((guardId, total)) : Some((guardId2, total2))
    }
  );
};

let maxMin = minuteMap =>
  minuteMap->Map.Int.reduce(None, (acc, minute, count) =>
    switch (acc) {
    | None => Some((minute, count))
    | Some((minute2, count2)) =>
      count2 > count ? Some((minute2, count2)) : Some((minute, count))
    }
  );

let part1 = input => {
  let minuteCountMap = input->sortInput->List.fromArray->process;
  let (guardId, _total) = maxMinAsleepGuardId(minuteCountMap)->Option.getExn;
  let minuteMap = minuteCountMap->Map.Int.get(guardId)->Option.getExn;
  let (minute, _count) = maxMin(minuteMap)->Option.getExn;
  guardId * minute;
};

let maxGuardMinute = map =>
  map->Map.Int.reduce(None, (acc, guardId, minuteMap) =>
    minuteMap->Map.Int.reduce(acc, (acc2, minute, count) =>
      switch (acc2) {
      | None => Some((guardId, minute, count))
      | Some((guardId2, minute2, count2)) =>
        count > count2 ?
          Some((guardId, minute, count)) : Some((guardId2, minute2, count2))
      }
    )
  );

let part2 = input => {
  let (guardId, minute, _count) =
    input->sortInput->List.fromArray->process->maxGuardMinute->Option.getExn;
  guardId * minute;
};
