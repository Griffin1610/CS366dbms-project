import pandas as pd
import requests
import time

INPUT_PATH = "/Users/griffinpolly/Downloads/temp/work.csv"
OUTPUT_PATH = "/Users/griffinpolly/Downloads/temp/work_updated.csv"
TARGET_MUSEUM_ID = 53 #Cleveland Museum of Art Integration
API_DELAY = 0.25

def fetch_cma_image(title):
    try:
        search_url = "https://openaccess-api.clevelandart.org/api/artworks/"
        params = {"q": title}
        resp = requests.get(search_url, params=params, timeout=10).json()

        results = resp.get("data", [])
        if not results:
            return None

        image_url = results[0].get("images", {}).get("web", {}).get("url")
        return image_url
    except Exception as e:
        print(f"Error for '{title}': {e}")
        return None

df = pd.read_csv(INPUT_PATH)

for idx, row in df[df["museum_id"] == TARGET_MUSEUM_ID].iterrows():
    print(f"Updating CMA artwork '{row['name']}' at row {idx}")
    url = fetch_cma_image(row["name"])
    if url:
        df.at[idx, "url"] = url
    else:
        print(f"No image found for '{row['name']}'")
    time.sleep(API_DELAY)

df.to_csv(OUTPUT_PATH, index=False)
print(f"Cleveland Museum of Art update complete. Saved to: {OUTPUT_PATH}")
