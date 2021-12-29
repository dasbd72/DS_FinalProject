# DS FinalProject

## Compile

`g++ -std=c++17 -o essay-search.exe ./\*.cpp -lstdc++fs`

## Execute

`./essay-search [data_folder_path] [query.txt] [output.txt]`

## Querry

- `Word` : prefix search
- `"Word"` : exact search
- `*Word*` : suffix search
- `\+` : and
- `/` : or
