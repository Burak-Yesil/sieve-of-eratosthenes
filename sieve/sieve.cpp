/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Burak Yesil
 * Date        : 09-13-2021
 * Description : Sieve of Eratosthenes
 * Pledge      : "I pledge my Honor that I have abided by the Stevens Honor System."
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

//Constructor
PrimesSieve::PrimesSieve(int limit) :
    is_prime_(new bool[limit + 1]), limit_(limit) {
    sieve();
}

//Displays the prime numbers
void PrimesSieve::display_primes() const {
    cout<<endl;
    cout<< "Number of primes found: " << num_primes_ << endl;
    cout<< "Primes up to " << limit_ << ":" << endl;

    if (num_primes_ == 1){
        cout << 2;
    }
    const int max_prime_width = num_digits(max_prime_),          
    primes_per_row = 80 / (max_prime_width + 1);

    //consider for single line 
    int count = 1;
    for (int i = 2; i <= max_prime_; i++) {
        if (is_prime_[i]){
                if (num_primes_ > primes_per_row){
                    cout << setw(max_prime_width);
                }

                if (count == primes_per_row){
                    cout << i << endl;
                    count = 1;
                }

                else{
                    if (i == max_prime_){
                        cout << i;
                        count++;
                    }
                    else{
                        cout << i << " ";
                        count++;
                    }
                }

        
            


            
        }

    }
}



int PrimesSieve::count_num_primes() const {
    int count = 0;
    //Maybe change this condition
    for(int i = 2; i <= limit_; i++){
        if(is_prime_[i]){
            count++;
        }
    }
    return count;
}


void PrimesSieve::sieve() {
    
    for (int i = 2; i<=limit_; i++){
        is_prime_[i] = true;
    }

    for (int i = 2; i <= sqrt(limit_); i++){
        if (is_prime_[i]){
            for (int j = (i * i) ; j <= limit_ ; j+= i ){
                is_prime_[j] = false;
            }
        }
    }

    //setting number of primes
    num_primes_ = count_num_primes();
    
    //Chooses the max prime number
    for (int i = limit_; i>2; i--){
        if (is_prime_[i]){
            max_prime_ = i;
            break;
        }
    }

}




int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int num_of_digits = 0;
    while (1){
        num = num/10;
        num_of_digits++;
        if (num<1) break;
    }

    return num_of_digits;
}




int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve * temp = new PrimesSieve(limit); 
    temp -> display_primes();
    delete temp;
    return 0;
}
