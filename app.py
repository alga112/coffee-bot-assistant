import requests, json
import datetime

def sendPhoto():
    TOKEN = "5078330798:AAEUwMca46y6fcvTAxSI8wERvp5sgfNQJjw"
    CHAT_ID = "1930387592"

    endpoint = requests.get('https://coffee.alexflipnote.dev/random.json').json()
    img = endpoint['file']
    requests.post(f'https://api.telegram.org/bot{TOKEN}/sendPhoto?chat_id={CHAT_ID}&photo={img}')


    today = datetime.datetime.now().strftime("%d-%m-%Y")# لي ارسال التاريخ مع الصورة كل 6 صباحا 
    text =  'صباح الخير ☕' + '\n' + str(today)

    reply_markup={"keyboard":[ # لصناعة كيبورد 
                                ["كمية حبوب القهوة ☕️","☕💲شراء بن قهوة"],
                                ["➕☕️","كم كوب شربت اليوم؟" ],
                                ["/start","🌟supportive push😎"]],"one_time_keyboard":False,"resize_keyboard":True}

    data = {'chat_id': CHAT_ID, 'text': text, 'reply_markup': json.dumps(reply_markup)}

    url = f"https://api.telegram.org/bot{TOKEN}/sendMessage"# url الخاص في ال api  الخاص للبوت لكي يرسل له 

    requests.post(url, data = data) # الارسال للبوت 

if __name__ == "__main__":
    sendPhoto()
