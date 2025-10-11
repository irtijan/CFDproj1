#include <vector>   // Header with vector fucntions used for array creation
#include <cmath>    // Header with math functions used for trig calculatons
#include <fstream>  // Header with output fucntions used for CSV creation
#include <print>    

int main() {

    int s = 32; // Plate grid size length

    std::vector<std::vector<double>> T_prev(s, std::vector<double>(s, 0.0));  // Temperature array T at n
    std::vector<std::vector<double>> T(s, std::vector<double>(s, 0.0));       // Temperature array T at n+1

    std::vector<double> l_inf;  // Convergence history vector
    double l_inf_tmp = 1.0;     // Convergence value to be found at each iteration

    int iter = 0;         // Iteration counter

    double T_btot = 0.0;  // Sum of boundary temperature points
    
    double diff = 0.0;    // Difference of temperature at point between n and n+1

    for (int i = 0; i < s; i++) {
            T_prev[0][i] = 0.0;
            T_prev[i][0] = 0.0;
            T_prev[s - 1][i] = std::sin(M_PI * i / (s - 1));
            T_prev[i][s - 1] = std::sin(M_PI * i / (s - 1));
            T_btot += T_prev[s - 1][i] + T_prev[i][s - 1];
        }
        // Loop to set boundary point temperatures

        double T_ic = T_btot / (4 * s - 4);  //  Initial interior temperature of boundary average

    for (int row = 1; row < s - 1; row++) {
        for (int col = 1; col < s - 1; col++) {
            T_prev[row][col] = T_ic;
        }
        // Loop to set interior points to initial temperature
    }

    T = T_prev; // Carrying over initial and boundary conditions to n+1 array
        
    while (l_inf_tmp > 1e-12) {
        l_inf_tmp = 0.0;
        for (int row = 1; row < s - 1; row++) {
            for (int col = 1; col < s - 1; col++) {
                T[row][col] = (T_prev[row + 1][col] + T_prev[row - 1][col] + T_prev[row][col + 1] + T_prev[row][col - 1]) / 4.0;
                diff = std::abs(T[row][col] - T_prev[row][col]);
                if (diff > l_inf_tmp) {
                    l_inf_tmp = diff;
                }
            }
        }
        T_prev = T;
        l_inf.push_back(l_inf_tmp);
        iter += 1;
        // Loop that iterates T and convergences once maximum difference of a point between n and n+1 is <1e-5
    }

    std::ofstream output_file1("T.csv");  // Creates CSV output file for T
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            output_file1 << T[i][j];
            if (j != T[i].size() - 1)
                output_file1 << ",";  // separate columns by commas
        }
        output_file1 << "\n"; // new line for each row
        // Loop thats transfer last T to CSV
    }

    output_file1.close();  // Closes output file

    std::ofstream output_file2("Convergence.csv");  // Creates CSV output file for convergence history
    for (int i = 0; i < iter; i++) {
        std::println(output_file2, "{},{}", i + 1, l_inf[i]);
        // Loop thats transfer last convergence history to CSV
    }

    output_file2.close();  // Closes output file

    std::vector<std::vector<double>> Texact(s, std::vector<double>(s, 0.0));  // Temperature array Texact

    double l_inf2 = 0.0;  // Error between exact and numerical solution
    double diff2 = 0.0;   // Difference of temperature at point between exact and numerical solution
    for (int row = 0; row < s; row++) {
        double y = double(row) / (s-1);
        for (int col = 0; col < s; col++) {
            double x = double(col) / (s-1);
            Texact[row][col] = (std::sinh(M_PI * y) * std::sin(M_PI * x)
                         + std::sinh(M_PI * x) * std::sin(M_PI * y))
                         / std::sinh(M_PI);
            diff2 = std::abs(Texact[row][col] - T[row][col]);
            if (diff2 > l_inf2) {
                l_inf2 = diff2;
            }
        }
    // Loop that that calculates exact T and finds error between numerical solution
    }

    std::ofstream output_file3("Texact.csv");  // Creates CSV output file for exact temperature array
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            output_file3 << Texact[i][j];
            if (j != Texact[i].size() - 1)
                output_file3 << ",";  // separate columns by commas
        }
        output_file3 << "\n"; // new line for each row
        // Loop thats transfers exact temperature array to CSV
    }

    output_file3.close();  // Closes output file

    std::print("L_inf2 = {}\n", l_inf2);     // Prints the error for the step size
    std::vector<int> step = {4, 8, 16, 32};  // Mesh size vector
    std::vector<double> error = {0.04980540832105074, 0.010253525465794, 0.0022759243329250056, 0.0005333793433820455};
    // error vector

    std::ofstream output_file4("error.csv");  // Creates CSV output file for mesh size vs error
    for (int i = 0; i < step.size(); i++) {
        std::println(output_file4, "{},{}", step[i], error[i]);
        // Loop thats transfers mesh size vs error to CSV
    }

    output_file4.close();  // Closes output file

    return 0;  // Ends program
}