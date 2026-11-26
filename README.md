# csv-data-checker

A small command-line tool written in C++ that checks CSV data files (like game item or level settings) for common mistakes, and tells you exactly which row is wrong.

## What it checks

- **Wrong column count:** a row has more or fewer values than the header.
- **Empty values:** a column is blank (spaces count as blank).
- **Duplicate IDs:** the first column (the ID) appears more than once.

## Build and run

Requires Visual Studio 2022 with the "Desktop development with C++" workload.

1. Open `csvcheck/csvcheck.sln` in Visual Studio and build it (Ctrl+Shift+B).
2. From the repository folder, run the tool on a CSV file:

```
csvcheck\x64\Debug\csvcheck.exe samples\good.csv
```

## Example

A file with a missing value (`samples/bad_empty.csv`):

```
id,name,price,stock
1,Burger,5.50,20
2,Fries,,50
3,,2.00,40
```

Running the tool prints:

```
Row 3: column 'price' is empty
Row 4: column 'name' is empty
2 problems found in 3 rows
```

Other sample files in `samples/` show the other checks: `bad_columns.csv` and `bad_duplicates.csv`.

## Exit codes

- `0`: no problems found
- `1`: problems found, or the file could not be opened

This makes it usable in a build script, which can stop when a data file is broken.

## Limitations

- Values are split at every comma, so quoted values that contain commas (such as `"Burger, Large"`) are not supported yet.
- The first column is always treated as the ID.

## What's next

- Support quoted values
- Choose which column is the ID
- Optional min/max rules for number columns

## License

MIT