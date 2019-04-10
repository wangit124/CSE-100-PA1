
#ifndef Timer_hpp
#define Timer_hpp

#include <chrono>

class Timer{
    
private:
    /** start the timer */
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    
public:
    
    /**
     * Function called when starting the timer.
     */
    void begin_timer() {
        start = std::chrono::high_resolution_clock::now();
    }
    
    /**
     * Function called when ending the timer. Returns duration in nanoseconds
     * PRECONDITION: begin_timer() must be called before this function
     */
    long long end_timer() {
        std::chrono::time_point<std::chrono::high_resolution_clock> end;
        end = std::chrono::high_resolution_clock::now();
        
        return (long long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    
    
};

#endif /* Timer_hpp */
