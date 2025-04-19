import pandas as pd
import requests
import time


INPUT_PATH = "/Users/griffinpolly/Downloads/temp/work.csv"
OUTPUT_PATH = "/Users/griffinpolly/Downloads/temp/work_updated.csv"
TARGET_MUSEUM_ID = 35 # Metropolitain Museum of Art
API_DELAY = 0.5

def fetch_met_image(title):
    try:
        search = requests.get(
            "https://collectionapi.metmuseum.org/public/collection/v1/search",
            params={"q": title, "hasImages": "true"},
            timeout=5
        ).json()

        ids = search.get("objectIDs")
        if not ids:
            return None

        obj = requests.get(
            f"https://collectionapi.metmuseum.org/public/collection/v1/objects/{ids[0]}",
            timeout=5
        ).json()

        return obj.get("primaryImage") or obj.get("primaryImageSmall")
    except Exception as e:
        print(f"Error for '{title}': {e}")
        return None

df = pd.read_csv(INPUT_PATH)
print("Columns found:", df.columns.tolist())


for idx, row in df[df["museum_id"] == TARGET_MUSEUM_ID].iterrows():
    print(f"Updating '{row['name']}' at row {idx}")
    url = fetch_met_image(row["name"])
    if url:
        df.at[idx, "url"] = url
    else:
        print(f"No image found for '{row['name']}'")
    time.sleep(API_DELAY)

df.to_csv(OUTPUT_PATH, index=False)
print(f"Saved updated file to:\n{OUTPUT_PATH}")
