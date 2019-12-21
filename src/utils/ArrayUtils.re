exception UnsafeFindFailed(string);

let copyAndSort = (f, t) => {
  let cp = t |> Array.copy;
  cp |> Array.sort(f);
  cp;
};

let isEmpty = a =>
  switch (a) {
  | [||] => true
  | _ => false
  };

let isNotEmpty = a => !(a |> isEmpty);

let flatten = t => {
  t |> Array.to_list |> List.flatten |> Array.of_list;
};

