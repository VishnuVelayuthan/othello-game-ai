
import pandas as pd 

def process_file(filename):
    # Load the CSV file
    df = pd.read_csv(filename)    

    df.columns = df.columns.map(lambda x: x.replace(' ', ''))
    
    # Prepare data: Extract relevant metrics based on the winner
    # For X winners, we're interested in X's performance metrics
    df_x = df[df['Winner'] == 'X'][['X_Tiles', 'X_Moves', 'X_LM']]
    # Rename columns for uniformity
    df_x.columns = ['Tiles', 'Moves', 'LM']
    
    # For O winners, we're interested in O's performance metrics
    df_o = df[df['Winner'] == 'O'][['O_Tiles', 'O_Moves', 'O_LM']]
    # Rename columns for uniformity
    df_o.columns = ['Tiles', 'Moves', 'LM']
    
    # Combine the dataframes
    combined_df = pd.concat([df_x, df_o])
    
    # Calculate the mean and standard deviation for Tiles, Moves, and LM
    results = {
        'mean': combined_df.mean().to_dict(),
        'std': combined_df.std().to_dict(),
    }
    
    return results


if __name__ == "__main__":

    output_file = "phase-statistics.txt"

    columns = ['Tiles', 'Moves', 'LM']
    stat_types = ["mean", "std"]

    for i in range(10):
        file_name = f"../../data/csv-snapshots/snapshot-{i}.csv" 
        # file_name = f"snapshot-{i}.csv" 
        stats = process_file(file_name)

        with open(output_file, "a") as f: 
            f.write("===================\n")
            f.write(f"For Snapshot {i}: \n")
            for column in columns:
                for stat_type in stat_types:
                    f.write(f"\t{column} {stat_type}: {stats[stat_type][column]}\n")
                       









