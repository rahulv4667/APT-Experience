# A.P.T Portfolio Interview Experience

[Coding Round](./README.md)
[Interview 1](./Interview1.md)

## Interview - Round 2 (2 hrs)


There were 2 interviewers when I joined the call. One of them asked me to write code for reversing a linked list. I told them that I was asked the same question previously. He then tried to change and explain the other question. But he wasn't able to. He took a minute and wrote the input and output. It was applying the partition algorithm on linked list when given a pivot. The partition algorithm from quick sort. I thought for a while. I was trying to explain what I was thinking. He told me to just code it first and then explain the approach. So, I wrote the boilerplate code. And started thinking. I asked if I could use extra space. NO. I asked if I could modify the data itself instead of playing with pointers. "What do you think will be acceptable?". "Obviously, the pointers", I said with an embarrassing smile. I thought for a while. I tried two pointers approach where, as I go along, I modify the `next` pointer of nodes to the ones they should be pointing at in the final linked list. But I could only do it for either elements that are less or more but not both. From there I got the final idea. Create a separate linked list for elements less than pivot, for pivot and for greater than pivot. [Code](./partition_ll.cpp).

The above question took around 20-30 minutes. The other interviewer told me there is some redundancy in code, I removed it. He told the code could still be optimized but whatever's there was fine. He asked me to go through the code and mention where each variable will be stored. I did that. 

Then the other interviewer asked questions related to OS and COA. 

Do you know what a TLB is? - Yes\
What is the difference between TLB and cache? - In TLB, we store page table entries. In cache, we store the actual data or pages.\
What are different types of cache? - You mean L1, L2, L3\
No. There are kinds right? Associative? - Yeah. Yeah. Direct. Associative. Set Associative.\
What is Associative cache? - I don't remember these things exactly but isn't it like we do hash, most likely mod operation, and store page table entry in respective bucket.\
No. No. That is set associative? We don't have buckets here - Yeah. Yeah. I meant we have a single entry for hash value.\
Does your laptop use RISC or CISC? - I guess CISC since I heard RISC is mostly used in smartphones. But I know there are RISC laptops too.\
What's your laptop? - Dell Inspiron 3567\
What was the second statement you made? - I heard RISC is mostly used in smartphones.\
Why do you think that is? - I think it's because they are simpler instructions. And need less power to execute. \
Which architecture do you think will need more registers? - (thought for a while) I guess RISC.\
Why so? - Maybe because the instructions are simpler, you will have to store more context during execution and hence more registers.\


There was a silence longer than usual but then they continued - "Fine. Understandable."

The coding interviewer asked another question. Given an array of elements, try to write an algorithm which can tell if it's possible to rearrange the array in such a way that the sum of adjacent elements is not divisible by 3. I couldn't answer this. The first thought I had was to make some kind of bipartite graph but I didnt know how to make edges. The interviewer told the answer is much simpler. I thought of keeping a separate visited array and find arrangements through two pointer technique. But I couldn't figure out what the time complexity would be. I took a lot of time. Interviewer said we will move on to other stuff. The [answer](https://www.geeksforgeeks.org/permutation-of-array-such-that-sum-of-adjacent-elements-are-not-divisible-by-3/) really is much simpler. 

Next I was asked related to OS.
What are system calls? - Do you mean actual syscalls or system calls API?\
The API. - They are the interface that the applications or users need to use to access hardware and make any changes to the state of the system.\
And what was the other one? - Syscalls. They are the actual functions that get executed in kernel mode.\
What is the difference between both of them? - So, a systemcall API is called by user or application in user mode but a syscall is executed in kernel mode. Actually, the API function that is used is just a wrapper for syscalls. The APi function just sets the environment like mode bit, registers etc for the syscall to execute. So, Multiple API functions can call the same syscall internally\
Can you give an example of multiple API functions calling the same syscall? - The `fork` function that is used to create a new process and `pthread_create` function that is used to create a new thread both used the same internal function `clone`.\
Do you know `exec`? - Do you mean `exit`. 
No, `exec`? Acha. Oh. Yeah.
What is it used for? - It is used to call other applications in the system. For example, if we want to open a text editor from our application we could execute `exec("gedit")` and gedit will open. \
Can we continue executing our code when using `exec`? - Not unless you use `fork`. When we use `fork`, our application runs on a different process from the one we called exec on. Without it, our application excution pauses till the `exec` application closes.\

The other interviewer asked another question which he said would involve all subjects.
 Given half million integers and 1MB RAM, sort the elements. Right away I knew this was external merge sort. But I clarified more since they might be trying to test OS, COA and the interviewer gave the disclaimer. I asked if I should consider call stack also part of this 1MB RAM. They said 1MB RAM is just for storage. 5million is `5x10^5`, and each integer is 4 bytes. So, total space needed would be `2^21` bytes assuming `10^6 = 2^20`. I asked clarification if I can make that assumption. They had no problem. I was trying to explain the approach. They asked me to write pseudocode. I took probably 10-15 minutes as I was getting confused. The following is the pseudocode I wrote.

```python
half_size=arr.size()/2
quarter_size=arr.size()/4

sort_arr = arr[0:half_size]
sort(sort_arr.begin(), sort_arr.end())
arr[0:half_size] = sort_arr     # writing back to disk

sort_arr = arr[half_size:arr.size()]
sort(sort_arr.begin(), sort_arr.end())
arr[half_size:arr.size()] = sort_arr # writing back to disk

for i in range(2):
    for j in range(2):
        merge_arr[0:quarter_size] = arr[i*quarter_size:(i+1)*quarter_size]
        merge_arr[quarter_size:half_size] = arr[half_size+j*quarter_size:half_size+(j+1)*quarter_size]
        merge(merge_arr.begin(), merge_arr.end(), 0, quarter_size, half_size)
        arr[i*quarter_size:(i+1)*quarter_size] = merge_arr[0:quarter_size]
        arr[half_size+j*quarter_size:half_size+(j+1)*quarter_size] = merge_arr[quarter_size:half_size]
```

There are 16 elements of arbitrary range. Which is the best sorting algorithm. I asked if we know anything about ordering of elements. NO. I said although quick sort executes with O(nlogn) time and O(1) space, it's worst case could go to O(n^2). So, merge sort is best even though it takes O(n) space as it takes O(nlogn) time. They asked if heap sort won't work. I was not even thinking of heap sort till then. But I wasnt sure if it was better than merge. I said I am not sure about its sppace complexity. They said its fine if I dont know heap sort. THey then asked me to list STL structures I know and their complexities. I started listing the STL containers I know but I couldn't get to the complexities. Don't remember telling them. But I do remember telling about an optimization that STL does with deque where instead of copying the old data when reallocating space, it just assigns a new block and has a pointer to it. 

Next,  another interviewer was added. He asked me to give an overall explanation of whole code that I wrote in coding test. I explained it.

Once CPU assigns memory to NIC and tells NIC to read from it, and continues executing other programs which execute on top of same memory location, wouldnt it be wrong? - They wont be executed since the buffer for NIC will be different from the buffer used for the program. Network activities will generally have a separate buffer.\

Ok. But a user can always find the address, seek to it and write to the address right? - (I don't remember what answer I gave but definitely not right because he mentioned virtual memory in next question which I never told).

Alright. Even though virtual memory is different for each process, we are essentially writing to the same physical disk space right. So, an attacker might try to find the mapping from virutal memory to physical and attack? - Yes but the buffers that we allocate for network are in kernel space. Generally the first 1GB of physical disk is allocated for kernel and its data structures.

Why would using kernel space be safe? - whenever u want to modify in kernel space, you need to make a system call and before any modification or read is done i from this space, it is changed to kernel mode where no other process can access this space. If u try to modify the physical location directly, since it checks if mode bit is set or not, it wont perform the operation.

You said there will be 1GB assigned to kernel. What happens when it needs more memory? Obviosuly sometimes it will need it right? - Yes. It could swap some of userspace to disk. Consider it as kernel space and do whatever operation is required. Once, the operation is done, it can clear out the memory it used and reload the user memory from disk.

Have you worked on any network related applications? - Yes. I wrote a bittorrent like file sharing system. 

Can you list the protocols that you used? - Umm. I used TCP for all communications.

Why so? You could have used UDP also right? - Yes. But I didn't want to handle errors when packets drop in UDP.

Hmm. Lets say we have implemented the error handling for UDP at application layer, are there any advantages of using UDP over TCP? - (I thought for a while) Maybe not immediately. But in future, when we are trying to make some custom optimizations ourselves, it could be helpful.


Ok. Cool. Anymore questions.
