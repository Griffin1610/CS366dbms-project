import pandas as pd
import requests
import time

INPUT_PATH = "/Users/griffinpolly/Downloads/temp/work.csv"
OUTPUT_PATH = "/Users/griffinpolly/Downloads/temp/work_updated.csv"
TARGET_MUSEUM_ID = 68
API_DELAY = 0.25

def fetch_aic_image(title):
    try:
        search_url = "https://api.artic.edu/api/v1/artworks/search"
        params = {"q": title}
        search_resp = requests.get(search_url, params=params, timeout=10).json()

        hits = search_resp.get("data", [])
        if not hits:
            print(f"No match found for: {title}")
            return None

        artwork_id = hits[0]["id"]
        obj_url = f"https://api.artic.edu/api/v1/artworks/{artwork_id}"
        obj_resp = requests.get(obj_url, timeout=10).json()

        image_id = obj_resp.get("data", {}).get("image_id")
        if not image_id:
            print(f"No image found for: {title}")
            return None

        return f"https://www.artic.edu/iiif/2/{image_id}/full/843,/0/default.jpg"

    except Exception as e:
        print(f"Error for '{title}': {e}")
        return None

df = pd.read_csv(INPUT_PATH)
for idx, row in df[df["museum_id"] == TARGET_MUSEUM_ID].iterrows():
    title = row["name"]
    url = fetch_aic_image(title)
    print(f"{title} → {url}")
    if url:
        df.at[idx, "url"] = url
    time.sleep(API_DELAY)

df.to_csv(OUTPUT_PATH, index=False)
print(f"AIC update complete. Saved to: {OUTPUT_PATH}")
