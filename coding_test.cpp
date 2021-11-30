#include <bits/stdc++.h>
using namespace std;

// The Wire class is already given
class Wire {
    public:
    static const int SOP = 254;
    static const int EOP = 255;

    uint8_t read_data() {
        uint8_t num;
        cin>>num;
        return num;
    }

    void write_data(uint8_t num) {
        cout<<num<<" ";
    }
};

// The following is the code written.
const int BLOCK_SIZE=1<<10;
const string CPU_NAME = "cpu";
const string NIC_NAME = "nic";

enum class InterruptType {
    MEM_ALLOC,      // used when NIC wants to request CPU for memory
    MEM_ALLOCED,    // used when CPU wants to tell NIC about successful allocation
    SEND_DATA,      // used when CPU completed processing and wants NIC to send data.
    PROCESS_DATA    // used when NIC wants CPU to process information
};


class InterruptEvent {
    public:
    InterruptType _type;
    uint8_t* ptr;
    uint64_t dsize;
    string sender;
    string receiver;

    InterruptEvent(InterruptType _type, uint8_t *ptr, uint64_t dsize, string sender, string receiver) 
    :   _type(_type),
        ptr(ptr),
        dsize(dsize),
        sender(sender),
        receiver(receiver)
    {

    }
};


class RAM {
    unordered_map<uint8_t*, uint64_t> mp;

    uint8_t* mem_alloc(uint64_t size) {
        uint8_t* mem = (uint8_t*)malloc(size);
        mp[mem] = size;
        return mem;
    }

    uint8_t* mem_realloc(uint8_t* old_ptr, uint64_t size) {
        uint8_t* new_ptr = (uint8_t*)realloc(old_ptr, size);
        mp.erase(old_ptr);
        mp[new_ptr] = size;
        return new_ptr;
    }
    void free_mem(uint8_t* ptr) {
        free(ptr);
    }
};

class MemCtrlr {
    RAM _ram;
    public:
        uint8_t* mem_alloc(uint64_t size) {
            return _ram.mem_alloc(size);
        }

        uint8_t* mem_realloc(uint8_t* old_ptr, uint64_t size) {
            return _ram.mem_realloc(old_ptr, size);
        }

        void free_mem(uint8_t* ptr) {
            free(ptr);
        }

        uint8_t read_data(uint8_t* ptr) {
            return *ptr;
        }

        void write_data(uint8_t* ptr, uint8_t value) {
            *ptr = value;
        }
};

class Peripheral {
    protected:
        PCIE pcie;
        string name;
    public:
        Peripheral(string name, PCIE pcie): name(name), pcie(pcie) {} 

        virtual void run() = 0;
        virtual void handle_interrupt(InterruptEvent evt) = 0;

        string getName() const { return name; }
};

class NIC: public Peripheral {
    uint8_t* current_buf;
    uint64_t curr_ptr;
    uint64_t total_size;
    Wire wire;
    public:
        NIC(string name, PCIE pcie, Wire wire)
        : Peripheral(name, pcie), 
            wire(wire) ,
            curr_ptr(0),
            total_size(0),
            current_buf(NULL)
        {
            pcie.register_peripherals(this);
        }

        void run() {
            if(total_size==0 || curr_ptr==total_size) return pcie.send_interrupt(InterruptEvent(
                InterruptType::MEM_ALLOC,
                current_buf,
                total_size+BLOCK_SIZE,
                NIC_NAME,
                CPU_NAME
            ));

            int num;
            while((num=wire.read_data()) != Wire::EOP) {
                current_buf[curr_ptr] = num;
            }

            return InterruptEvent(
                InterruptType::PROCESS_DATA,
                current_buf,
                curr_ptr,
                NIC_NAME,
                CPU_NAME
            );
        }

        void handle_interrupt(InterruptEvent evt) {
            switch evt._type {
                case InterruptType::MEM_ALLOC: break;
                case InterruptType::MEM_ALLOCED:
                    curr_buf = evt.ptr;
                    used_size = total_size;
                    total_size += BLOCK_SIZE;
                    run();
                    break;
                case InterruptType::SEND_DATA:
                    wire.write_data(Wire::SOP);
                    for(int i=0; i<used_size; i++) {
                        wire.write_data(ptr[i]);
                    }
                    wire.write_data(Wire::EOP);
                case InterruptType::PROCESS_DATA:
            }
        }
};

class CPU {
    MemCtrlr mctrlr;

    public:
    CPU(MemCtrlr mctrlr) : mctrlr(mctrlr) {}

    void handle_interrupt(InterruptEvent evt) {
        switch evt._type {
            case InterruptType::MEM_ALLOC:
                uint8_t* ptr = (evt.ptr==NULL)?mctrlr.mem_alloc(evt.size):mctrlr.mem_realloc(evt.ptrm evt.size);
                return InterruptEvent(InterruptType::MEM_ALLOCED, ptr, evt.size, CPU_NAME, evt.sender);
            case InterruptType::MEM_ALLOCED: break;
            case InterruptType::SEND_DATA: break;
            case InterruptType::PROCESS_DATA:
                sort(evt.ptr, evt.ptr+evt.size);
                return InterruptEvent(InterruptEvent::SEND_DATA, evt.ptr, evt.size, CPU_NAME, evt.sender);
        }
    }
};

class PCIE {
    CPU _cpu;
    vector<Peripheral*> peripherals;

    public:
        bool register_peripherals(Peripheral* peripheral) {
            peripherals.push_back(peripheral);
        }

        void send_interrupt(InterruptEvent evt) {
            for(int i=0; i<peripherals.size(); i++) {
                if(peripherals[i]->getName() == evt.receiver) 
                    peripherals[i]->handle_interrupt(evt);
            }
        }
};