#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>  
#include <ArduinoJson.h>
const char* ssid = "Home-4G";
const char* password = "0500576175";
#define BOTtoken "5078330798:AAEUwMca46y6fcvTAxSI8wERvp5sgfNQJjw" 
#define CHAT_ID "1930387592"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

// التاكد من اذا يوجد راسلة كل ثانية واحدة (delay=1000) 
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int trigPin = 5;
const int echoPin = 18;
int cups=0;
#define SOUND_SPEED 1
long duration;
int distanceCm;
void d(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_SPEED/2;
if(distanceCm<650){
  Serial.print("Distance: ");
  Serial.println(distanceCm);
 }
  delay(1000);
  }
// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    // Chat id of the requester
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Unauthorized user", "");
      continue;
    }
    
    //طباعة الرسالة الترحيبية 
    String text = bot.messages[i].text;
    Serial.println(text);

    String from_name = bot.messages[i].from_name;

    if (text == "/start") {
      String welcome = "Welcome, " + from_name + ".\n";
      welcome += "استخدم الازرار الموجودة امامك 🛑.\n\n";
      welcome += "➕☕️\n";
      welcome += "هل انتهت الكمية ☕\n";
      welcome += "كم كوب شربت اليوم؟\n";
      welcome += "☕💲شراء بن قهوة\n\n";
       welcome += "🌟supportive push😎";
      bot.sendMessage(chat_id, welcome, "");
      cups=0;
    }
    if (text == "☕💲شراء بن قهوة"){ //ارسال الروابط
                                      String link1="https://beyyak.com/VoYgqv";
                                       bot.sendMessage(chat_id, link1, "");
                                       bot.sendMessage(chat_id, "https://beyyak.com/zaVdql", "");
                                       bot.sendMessage(chat_id, "https://beyyak.com/wwaWlm", "");
                                       bot.sendMessage(chat_id, "https://beyyak.com/qEeWPN", "");
   }
                      // امر ارسال لمعرفة الكمية 
    if (text == "كمية حبوب القهوة ☕️"){if (distanceCm<=62){bot.sendMessage(chat_id, "كمية حبوب القهوة المتبقية 100%💯");}  
                                    else if (distanceCm<=124){bot.sendMessage(chat_id, "كمية حبوب القهوة المتبقية 90%🛑");}
                                    else if (distanceCm<=249){bot.sendMessage(chat_id, "كمية حبوب القهوة المتبقية 70%🛑");}
                                    else if (distanceCm<=312){bot.sendMessage(chat_id, "كمية حبوب القهوة المتبقية 60%🛑");}
                                    else if (distanceCm<=374){bot.sendMessage(chat_id, "كمية حبوب القهوة المتبقية 50%🛑");}
                                    else if (distanceCm<=499){bot.sendMessage(chat_id, "كمية حبوب القهوة المتبقية 30%🛑");}
                                    else if (distanceCm<=561){bot.sendMessage(chat_id, "كمية حبوب القهوة المتبقية 20%🛑");}
                                    else if (distanceCm<=610){bot.sendMessage(chat_id, "كمية حبوب القهوة المتبقية 10%🛑");}
                                    if (distanceCm>=610){
                                      String link1="https://beyyak.com/VoYgqv";
                                       bot.sendMessage(chat_id, link1, "");
                                       bot.sendMessage(chat_id, "https://beyyak.com/zaVdql", "");
                                       bot.sendMessage(chat_id, "https://beyyak.com/wwaWlm", "");
                                       bot.sendMessage(chat_id, "https://beyyak.com/qEeWPN", "");
  }
   /*if(distanceCm>=561){
     bot.sendMessage(chat_id, "🛑كمية حبوب القهوة بدات تقل قم بشراء المزيد......قم بالضغط على زر (☕💲شراء بن قهوة) لشراء البن المفضل لديك 🌟☕🌟💲");
  }*/
}
               //امر لزيادة الاكواب في كل مرة يتم ضغط الزر فيها 
    if(text == "➕☕️"){
       if (cups<4){
       cups ++;
       String mystring= String (cups);
       String phrase = " عدد الاكواب التي تناولتها للان  " + mystring + " اكواب من 4 ";
       bot.sendMessage(chat_id, phrase, "");
       if (cups==4){bot.sendMessage(chat_id, "🛑 لقد استهلكت الحد الاعلى من عدد الاكواب الموصى بها من هيئة الغذاء والدواء -- 4 اكواب --", "");}
       }
       else{
        bot.sendMessage(chat_id, "🛑 لقد استهلكت الحد الاعلى من عدد الاكواب الموصى بها من هيئة الغذاء والدواء -- 4 اكواب --", "");
       }
   }     
   if(text == "كم كوب شربت اليوم؟"){
       String mystring= String (cups);
       String phrase = " لقد شربت " + mystring + "من اصل 4 اكواب"; //كتابة رسالة في حين ضغط زر (كم كوب شربت اليوم ؟)
       bot.sendMessage(chat_id, phrase, "");  // ارسال امر للبوت بأرسال لسيرفر التليجرام 
   }  
  if(text == "🌟supportive push😎"){  // رسائل الدفعة المعنوية 
     String mylist[48] = {
     "{واتقوا اللَّه لعلكم تفلحون} (وآل عمران 200)","لا يتكبر إلا كل وضيع ، و لا يتواضع إلا كل رفيع✨🕊💖",
     "﴿ واذكر اسم ربّك وتبتل إليه تبتيلًا ﴾[المزمل: 8]","التكنولوجيا نجحت في تحديد موقعك على الأرض , تبقّى البحث عن تقنية تحدد فيها: موقعك في الحياة.🦾🕊🖤",
     "صحة الجسم في قلة الطعام وصحة القلب في قلة الذنوب والآثام وصحة النفس في قلة الكلام.🍽👌💖"," ﴿ ادعوا ربكم تضرعًا وخفيةً إنه لا يحب المعتدين ﴾[الأعراف: 55].",
     "المال يستر رذيلة الأغنياء ، و الفقر يغطي فضيلة الفقراء👏✨💲","يستطيع الكذب أن يدور حول الأرض في انتظار أن تلبس الحقيقة حذاءها🕊💛",
     "{اللَّه ولي الذين آمنوا يخرجهم من الظلمات إلى النور} ﴿٢٥٧ البقرة ﴾.","﴿ قد أفلح من تزكى * وذكر اسم ربه فصلى ﴾[الأعلى: 14، 15].",
     "{ثم ننجي الذين اتقوا ونذر الظالمين فيها جثيا} (مريم 72).","﴿ وأنفقوا في سبيل اللَّه ولا تلقوا بِأيديكم إلى التهلكة وأحسنوا إن اللَّهَ يحب المحسنين ﴾[البقرة: 195].",
     "لا كاسات خمر هنا، لكن خمراً تدور، لا دخان، بل لهب، اسمعوا الأصوات خافقة، بما تنخر به الأنغام جلال الدين الرومي","إن الفقر ليس خطيئةوإنما الخطيئة أن يكون المرء غنيا فيُهين الآخرين فيودور دوستويفسكي فنان,كاتب,روائي (1821 - 1881)🛑💲",
     "﴿ وَاصْبِرْ لِحُكْمِ رَبِّكَ فَإِنَّكَ بِأَعْيُنِنَا وَسَبِّحْ بِحَمْدِ رَبِّكَ حِينَ تَقُومُ * وَمِنَ اللَّيْلِ فَسَبِّحْهُ وَإِدْبَارَ النُّجُومِ ﴾[الطور: 48، 49].","الجراح الجيد يجب أن يكون لديه عينا نسر و قلب أسد و يد امرأة💊⭐", 
     "السلم شيء سريع العطب تماما مثل الصحة، فهو بحاجة إلى كثير من الظروف الملائمة والإرادات الحسنة المتضافرة.جاستون بوتول💖🌹","أولئك يجزون الغرفة بما صبروا ويلقون فيها تحيةً وسلامًا ﴾[الفرقان: 75].",
     "من المحتمل ألا تستطيع التحكم في الظروف ، و لكنك تستطيع التحكم في أفكارك ، فالتفكير الايجابي يؤدي الى الفعل الايجابي و النتائج الايجابية .ابراهيم الفقهي🌹✨❤","الثقة بالنفس هو ان تعتقد في نفسك اعتقاداً راسخاً بامكانية تحقيق الهدف باذن الله رغم جميع الظروف و التحديات💪",
     "قد لا تعينك الظروف و لا يساعدك من حولك و لكن… هنا يظهر التحدي و تظهر قوة إرادتك (استعن بالله… ولا تعجز ) ....نبيل العوضي","لقد خنقت الظروف طموحي. ميخائيل ليرمنتوف",
     "انها مجرد وظيفة. ينمو العشب، و الطيور تطير ، و الموج يقصف الرمال. و أنا أضرب الناس....محمد علي كلاي","الخيال تمرد على ظروف الزمان و المكان....سلمان العودة",
     "لن تستطيع أن تمنع طيور الهم أن تحلق فوق رأسك ولكنك تستطيع أن تمنعها من أن تعشش في راسك... مثل فرنسي🕊","أؤمن بدين الإسلام . أنا أؤمن بالله و بالسلام....محمد علي كلاي 🥊",
     "كل مؤسسة هي مؤسسة تعليمية وتعليمية. يجب أن يتم تضمين التدريب والتطوير فيه على جميع المستويات ، والتدريب والتطوير الذي لا يتوقف أبدًا.","الناس أعداء ما جهلوا.... علي بن ابي طالب رضي الله عنه",
     "أولئك يؤتون أجرهم مرتين بما صبروا ويدرؤون بالحسنة السيئة ومما رزقناهم ينفقون ﴾[القصص: 54].","﴿ وَاصْبِرْ وَمَا صَبْرُكَ إِلَّا بِاللَّهِ وَلَا تَحْزَنْ عَلَيْهِمْ وَلَا تَكُ فِي ضَيْقٍ مِمَّا يَمْكُرُونَ ﴾[النحل: 127",
     "الحرب هي السلام العبودية هي الحرية الجهل هو القوة⚔","إن الجيوشَ إنما تكثُر بالنصر وتقلُّ بالخذلان....خالد ابن الوليد رضي الله عنه✨",
     "Difficult roads often lead to beautiful destinations.🌹❤","الجيش أسد والأسد لا يأكل أولاده !؟...عبد الفتاح السيسي",
     "هناك دائما جانب مضيء اليوم قاس والغد أكثر قسوة وبعد غد جميل...جاك ما ملياردير صيني","The pain you feel today will be the strength you feel tomorrow",
     "لا تخف من أن تكون أول شخص يقوم بذلك كل شيء مستحيل حتى يفعل شخص ذلك...بروس واين😎","أبدا صغيرًا فكر كبيرًا لا تقلق على أشياء كثيرة في نفس الوقت أبد بالأشياء البسيطة أولا ثم تقدم إلى ألأشياء الأكثر تعقيدًا...ستيف جوبز🦾",
     "ليس كل شخص نعتك بالفاشل يعني انك فاشل!....امي🌟","لن تحصل على 60000 دولار سنوياً فقط بمجرد أنك تخرجت من الجامعة...بيل غيتس ",
     "الوقت الصعب يولد رجلاً ناجحاً🌟","كن مع الله دائيما....امي🌠🌠",
     "👊I will show you how great I am..محمد علي كلاي","التعليم الرسمي يجعلك تعيش، والتعليم الذاتي سوف يجلب لك ثروة...جيم رون",
     "كلمة سر النجاح هي (ابدا!)","WAKE UP TO REALITY NOTHING EVER GOES PLANNEDIN THIS A CCURSED WORLD",
     "﴿ ادْخُلُوا الْجَنَّةَ بِمَا كُنْتُمْ تَعْمَلُونَ ﴾[النحل: 32].","{ثم ننجي الذين اتقوا ونذر الظالمين فيها جثيا} (مريم 72)",
  };
     int selected = random(48);
     bot.sendMessage(chat_id, mylist[selected],"");
    }
  }
}
void setup(){
  Serial.begin(115200); //تهيئة السيريل مونيتور 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); // تعريف بينس الاترا سونك 
  #ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
    client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  #endif

  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  #ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  #endif
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
}

void loop() {
  d();
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}
