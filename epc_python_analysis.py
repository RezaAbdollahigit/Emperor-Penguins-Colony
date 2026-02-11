import numpy as np
import matplotlib.pyplot as plt

# --- 1. Configuration & Constants ---
POPULATION_SIZE = 20
DIMENSIONS = 10
MAX_ITERATIONS = 100

# EPC Parameters
SPIRAL_A = 1.0
SPIRAL_B = 0.5
MU_START = 0.05 # shows how much fast the heat fades
M_START = 0.5   # how much the penguins wiggle(mutate)

class EPCOptimizer:
    def __init__(self, func_name):
        self.func_name = func_name
        self.mu = MU_START
        self.m = M_START
        # Initialize population: Random values between -10 and 10 
        self.colony = np.random.uniform(-10, 10, (POPULATION_SIZE, DIMENSIONS))
        self.fitness = np.zeros(POPULATION_SIZE)
        self.best_history = []

    # --- 2. Benchmarks ---
    def calculate_fitness(self, x):
        if self.func_name == 'Sphere':
            return np.sum(x**2)
        elif self.func_name == 'Rosenbrock':
            # Vectorized Rosenbrock implementation
            return sum(100.0*(x[1:]-x[:-1]**2.0)**2.0 + (1-x[:-1])**2.0)
        return 0

    # --- 3. Main Algorithm Loop ---
    def optimize(self):
        print(f"--- Starting Optimization for {self.func_name} ---")
        
        for t in range(MAX_ITERATIONS):
            # Evaluate Fitness 
            for i in range(POPULATION_SIZE):
                self.fitness[i] = self.calculate_fitness(self.colony[i])
            
            # Identify Best Penguin 
            best_idx = np.argmin(self.fitness)
            best_pos = self.colony[best_idx].copy()
            self.best_history.append(self.fitness[best_idx])
            
            # Generate new positions
            new_colony = self.colony.copy()
            
            for i in range(POPULATION_SIZE):
                if i == best_idx:
                    continue # The best one doesn't move towards itself
                
                # Calculate Distance & Heat Attenuation (Q) 
                # Distance between penguin i and best penguin
                dist_sq = np.sum((best_pos - self.colony[i])**2)
                Q = np.exp(-self.mu * np.sqrt(dist_sq)) # attraction, the closer the stronger attraction
                
                # --- Movement Logic (Matching hw_accelerator.cpp) ---
                # Note: This matches your friend's implementation
                # Base movement towards the best penguin
                spiral_base = (1.0 - Q) * self.colony[i] + (Q * best_pos)
                
                # Random mutation component 
                # To prevent everyone from getting stuck in a bad spot, a small random "wiggle" is added to their movement
                u = np.random.uniform(-1, 1, DIMENSIONS)
                
                # Update Position 
                new_colony[i] = spiral_base + (self.m * u)
                
            self.colony = new_colony
            
            # Update Control Parameters 
            self.mu *= 0.99
            self.m *= 0.99
            
            if t % 20 == 0:
                print(f"Iter {t}: Best Fitness = {self.fitness[best_idx]:.6f}")

        print(f"Final Best Fitness ({self.func_name}): {self.fitness[best_idx]:.6f}\n")
        return self.best_history

# --- 4. Execution & Plotting ---
if __name__ == "__main__":
    # Run for Sphere
    sphere_opt = EPCOptimizer("Sphere")
    sphere_hist = sphere_opt.optimize()
    
    # Run for Rosenbrock
    rosen_opt = EPCOptimizer("Rosenbrock")
    rosen_hist = rosen_opt.optimize()
    
    # Plotting Results (Analysis Part) 
    plt.figure(figsize=(10, 5))
    plt.plot(sphere_hist, label='Sphere Function', linewidth=2)
    plt.plot(rosen_hist, label='Rosenbrock Function', linewidth=2)
    plt.yscale('log') # Log scale to see convergence better
    plt.title('EPC Algorithm Convergence Analysis')
    plt.xlabel('Iterations')
    plt.ylabel('Cost (Fitness) - Log Scale')
    plt.legend()
    plt.grid(True)
    plt.savefig('epc_convergence_plot.png') # Save plot for report
    plt.show()