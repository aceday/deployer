import sys
import re

def convert_collation(input_file, output_file, source_collation='utf8mb4_0900_ai_ci', target_collation='utf8mb4_general_ci'):
    try:
        with open(input_file, 'r', encoding='utf-8') as infile:
            sql_data = infile.read()
        
        # Replace all occurrences of the source collation
        updated_sql = re.sub(source_collation, target_collation, sql_data)

        with open(output_file, 'w', encoding='utf-8') as outfile:
            outfile.write(updated_sql)

        print(f"Conversion completed successfully. Output saved to: {output_file}")

    except FileNotFoundError:
        print(f"Error: File not found: {input_file}")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

# Entry point
if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python mysql_conv.py <source.sql> <dest.sql>")
    else:
        source_file = sys.argv[1]
        dest_file = sys.argv[2]
        convert_collation(source_file, dest_file)
