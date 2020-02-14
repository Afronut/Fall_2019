## Owner: Coovi Meha

## E_mail: Coovi.meha@colorado.edu

This contains multiple C files and a bash file named PA3.
The program read in the hostname in the file input with requester threads(s) and look up the IP with resolver Threads.
The resolver threads wait for the requester thread to read in half of the files first.
Requester add new hostname to the queue from head and revolvers lookup for ip and dequeue the queue from tail.

- PA3

## How-To:

- You do not need to enter input file. The program will take care of that. However
- You need to have ../input folder in this directory
- You might need to change permission to the PA3 bash file to allow execution.

```
./PA3  $req_thread $rev_thread $req_log $rev_log
```

```Run memory leak.
./PA3  leak  //You need to have the input folder in this directory
```

```Run All 6 Tests.
./PA3  test  //You need to have the input folder in this directory
```

```clean .o files.
./PA3  clean
```

```Purge .txt and built app.
./PA3  purge
```

## You can bypass the above method and run.

- Note: Also Every test must be run manually

```
make
```

then

```
./multi_lookup req_thread rev_thread req_log rev_log path_to_input [files]
```
