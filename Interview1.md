# A.P.T Portfolio Interview Experience

[Coding Round](./README.md)\
[Interview 2](./Interview2.md)

## Interview - Round 1 (1.25 hrs)

Interviewer was nice. He was patient when my earphones didn't work. He made some small talk about problems of things being online and studying from home. He started with my resume. I had a project in which I implemented a consensus algorithm. He asked questions related to it. How do leader elections happen? What happens when some nodes are lacking the updated information when network failures happen? This discussion was around 20-25 minutes I guess.

Then, he **gave the following code snippet and asked me what the output would be.**
```cpp
struct Point {
    int x;
    int y;
};
void modify(Point* p) {
    Point* a = new Point{6, 5};
    p = a;
}

int main() {
    Point* p = new Point{3, 4};
    modify(p);
    cout<<(p->x)<<" "<<(p->y)<<"\n";
}
```

I said the output would be `6 5`. But that was wrong. It is `3 4`. He asked me to explain why the output is that. I answered that although `p` is a pointer, the pointer variable itself is considered local in `modify`. He **asked me to change the signature of the function in such a way that it gets modified correctly.** I said we could use references and changed it to folowing:
```cpp
void modify((Point*)& p) {
```    

This gave the error `undeclared identifier p`. I couldn't figure out why. I tried to use double pointer. Don't remember the changes I made but the code didn't work because the pointer variable was still considered local. He asked to go back to the initial code and think again. He asked why am I putting brackets. Do we need brackets. I then tried
```cpp
void modify(Point*& p) {
```
It worked. He asked me why it wasn't working previously. I explained that it was considering `((Point*)& p)` as a typecast of a reference and since `p` was not declared yet in the scope of function, it was giving `undeclared identifier p` error. He asked me why I was using brackets. I told him that I was trying to make things explicit that I want a reference of this. He smiled understandably and moved on to next question. Thankfully he didnt think I don't know operator precedence and associativity.

The next was same question. This was asked in Apple too. **Output of following code.**

```cpp
char* some_func(char* str) {
    char s[] = "hello";
    str = s;
    return str;
}

int main() {
    
    char* str;
    str = some_func(str);
    
    cout<<str<<"\n";
    
    return 0;
}
```

I explained that since the string `"hello"` is local, the output will be either garbage value or `NULL` value. (I said `NULL` because when one of my friends ran the code during apple test, it showed `NULL`.) The interviewer was satisfied and was about to move on to next question but I asked him what would the real answer be - garbage or `NULL`. He said garbage. We were probably at around 45-50 minute mark right now. 

He gave me a coding question. **If there are 3k+1 elements in an array where k numbers repeat thrice and one is distinct. Find the distinct one.**

I was thinking out loud saying if it was repeating twice, we could do it with bitwise XOR. I mentioned the obvious solutions like 1-having a frequency map, 2- sorting. I myself said that since these easy solutions take `nlogn`, either space or time, I think optimal complexity will be `O(n)` time and `O(1)` for space. He agreed. I started thinking. Since it is repeating thrice, I was thinking if I would be able to do something by finding sum of numbers. The interviewer gave a minute if I am able to get somewhere. Then he said to think only in terms of bitwise operations.  I then tried to take an example and write bit representations. Then it clicked. We could try to find number of times each bit of 32 bits is set in the array. If the number of times it is set is divisible by 3, then it won't be present in the distinct element. 

Example:
Say the array is `1,2,2,1,7,3,7,2,7`
Bit representation of `1`  - `001` x 3
Bit representation of `2`  - `010` x 3
Bit representation of `3`  - `011` x 1
Bit representation of `7`  - `111` x 3
Num. of times each bit set - `377`

`3` divisible by three - so distinct element as of now - `0XX`
`7` is not divisible by three - so distinct element - `01X`
`7` is not divisible by three - so distinct element - `011`

He didn't ask me to write code for this. We were around 50-55 minute mark here. His next words - "Let's move on to some standard questions. **Write code for reversing a linked list.**" I wrote the boilerplate code and sighed saying "Although it is a standard question, I never did it thinking it is too simple".(I wasn't lying) He laughed. I tried to code iterative solution and I was half way there. But I was getting confused, so I asked if I could do recursive approach. He said since you reached so far in iterative one, stick to it. There was one pointer update that I was doing wrong. He said I could leave it if I want since the time is almost over. I said that I will try completing it since it is too basic a thing to not be able to do in an interview. He laughed and said ok. I was taking more time. He read the code and pointed out some unnecessary updations I was doing and the lack of one. With that, I completed it. In between there were couple of other questions - **what does `new` do and what are `namespace`s in C++.**

We were way out of time, around 75-80 minutes. He asked me if there were any questions. I asked about the work, clarifying his name since they were different in google meet and hackerrank window, what would be the next rounds since it wasn't informed to us. He said "If you qualify to the next round. (Pause). You qualified to the next round anyway. There will be another round of coding questions and you will be asked questions related to OS, COA, Networks". I said thank you and we ended the call. Within 10 minutes, I got informed about second round.   

