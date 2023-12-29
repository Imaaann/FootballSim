#include<stdio.h>
#include<windows.h>
#include<time.h>

void say(char *str)
{
    int i = 0 ;
    for(int i =0 ; str[i]!='\0';i++){
        printf("%c",str[i]);
        Sleep(75);
    }
}

int main()
{
    int dice;
    srand(time(NULL));
    dice=rand()%3;
    // 1v1 against the goalkeeper and it ends up with scoring
    switch(dice){
        case 0:
            say("Hold onto your seats, folks, because we're witnessing a symphony of teamwork unfolding on the pitch! It all starts with ");
            say(<player1>);
            say(", who picks up the ball deep in their own half. With a burst of speed, they leave defenders trailing in their wake. A quick one-two with ");
            say(<Player2>);
            say(" sees them slicing through the opposition's defense like a hot knife through butter. Now, ");
            say(<Player1>);
            say(" is faced with the goalkeeper ");
            say(<goalkeeper_name>);
            say(", but instead of going for glory, they unselfishly square the ball to ");
            say(<Player3>);
            say(" on the edge of the box. The defenders are caught off guard, and ");
            say(<Player3>);
            say(" calmly slots the ball into the back of the net. It's a goal created through the perfect combination of pace, vision, and teamwork. The crowd goes wild!");
            break;
        case 1:
            say("Here comes ");
            say(<team1>);
            say(" on the offensive! ");
            say(<Player1>);
            say(" initiates the attack, picking up the ball in midfield with a sublime piece of control. He threads a perfectly weighted pass to ");
            say(<Player2>);
            say(", who's making a darting run down the right flank. ");
            say(<Player2>);
            say(" showcases his blistering pace, leaving defenders in his wake. Sensing danger, he delivers a pinpoint cross into the box.\n");
            say("Enter ");
            say(<Player3>);
            say("! He times his run to perfection and meets the cross with a powerful header, forcing a brilliant save from the goalkeeper ");
            say(<goalkeeper_name>);
            say(". However, the rebound falls kindly to ");
            say(<Player3>);
            say(", who shows composure and slots the ball home with finesse in a 1v1 situation. What a sequence of play by ");
            say(<team1>);
            say(", orchestrated by the brilliance of ");
            say(<Player1>);
            say(", ");
            say(<Player2>);
            say(", and finally finished off by ");
            say(<Player3>);
            say("!");

            break;
        case 2:
            say("An exquisite attacking build-up from ");
            say(<team1>);
            say(" unfolds!\n");
            say(<Player1>);
            say(" orchestrates the play from deep, spraying a long-range pass to ");
            say(<Player2>);
            say(" on the left wing. ");
            say(<Player2>);
            say(" dazzles with his fancy footwork, leaving defenders bewildered as he cuts inside. With a quick exchange of passes, ");
            say(<Player2>);
            say(" finds ");
            say(<Player3>);
            say(" making a clever run into the penalty area.\nNow it's a 2v1 situation! ");
            say(<Player3>);
            say(" and ");
            say(<Player2>);
            say(" combine brilliantly, leaving the opposition scrambling. ");
            say(<Player3>);
            say(" receives the ball back from ");
            say(<Player2>);
            say(", leaving him with only the goalkeeper ");
            say(<goalkeeper_name>);
            say(" to beat. In a clinical fashion, ");
            say(<Player3>);
            say(" calmly slots the ball into the net, showcasing teamwork and individual skill in a breathtaking attack.");
            
            break;

    }

// 1v1 against the goalkeeper and it ends up with the goalkeeper clutching

    switch (dice)
    {
        case 0:
            say("And here comes ");
            say(<team1>);
            say(" on the offensive! It all starts with a pinpoint pass from <Player1> in the heart of the midfield. ");
            say(<Player2>);
            say(" receives the ball with grace on the edge of the box, showcasing incredible ball control. With a quick one-two, ");
            say(<Player3>);
            say(" becomes the recipient of a clever backheel from ");
            say(<Player2>);
            say(".\nNow ");
            say(<Player3>);
            say(" is through on goal, facing the imposing figure of ");
            say(<Goalkeeper>);
            say("! As the crowd holds its breath, ");
            say(<Player3>);
            say(" goes for a powerful strike, but ");
            say(<Goalkeeper>);
            say(" reacts brilliantly, diving to his left to make a stunning save. The stadium erupts with applause for ");
            say(<Goalkeeper>);
            say("'s heroics, denying ");
            say(<team1>);
            say(" a chance to score.");
            break;
        case 1:
            say("A mesmerizing attack from ");
            say(<team1>);
            say(" unfolds! ");
            say(<Player1>);
            say(" initiates the play with a visionary long ball, finding ");
            say(<Player2>);
            say(" on the wing. ");
            say(<Player2>);
            say(" embarks on a dazzling run, leaving defenders trailing in his wake. He cuts inside and lays off a perfectly weighted pass to ");
            say(<Player3>);
            say(", who finds himself in a 1v1 situation with ");
            say(<Goalkeeper>);
            say(".\nThe tension rises as ");
            say(<Player3>);
            say(" takes on ");
            say(<Goalkeeper>);
            say("! However, ");
            say(<Goalkeeper>);
            say(" stands tall, guessing the direction of the shot and making a spectacular save to keep the scores level. An incredible display of goalkeeping prowess to deny ");
            say(<team1>);
            say(" a golden opportunity.");

            break;
        case 2:
            say(<team1>);
            say(" orchestrates a beautiful sequence of passes in the attacking third! It begins with ");
            say(<Player1>);
            say("'s vision as he picks out ");
            say(<Player2>);
            say(" making a darting run down the flank. ");
            say(<Player2>);
            say(" delivers a precise cross into the box, where ");
            say(<Player3>);
            say(" times his run to perfection, finding himself with only ");
            say(<Goalkeeper>);
            say(" to beat.\nIt's a tense 1v1 situation, and ");
            say(<Player3>);
            say("goes for the chip! But wait, ");
            say(<Goalkeeper>);
            say(" reads it perfectly, soaring through the air to make a fantastic save. The crowd is in awe of ");
            say(<Goalkeeper>);
            say("'s acrobatics, denying ");
            say(<team1>);
            say(" a goal in spectacular fashion.");
            break;
    
    }

    // direct goal attacks

    switch (dice)
    {
        case 0:
            say("The play unfolds with a burst of creativity from ");
            say(<Player1>);
            say(", who dances past defenders with incredible skill. Spotting ");
            say(<Player2>);
            say(" in a pocket of space on the edge of the box, ");
            say(<Player1>);
            say(" delivers a perfectly weighted pass. The crowd holds its breath as ");
            say(<Player2>);
            say(" controls the ball with finesse, setting the stage for something extraordinary.\nEnter ");
            say(<Player3>);
            say("! Positioned just inside the penalty area, he times his run to perfection. With a majestic leap, ");
            say(<Player3>);
            say("connects with ");
            say(<Player2>);
            say("'s pinpoint cross, executing a breathtaking bicycle kick! The ball rockets off his boot with precision and power, leaving the goalkeeper ");
            say(<Goalkeeper>);
            say(" rooted to the spot.\nIn an awe-inspiring moment, time seems to stand still as the ball sails towards the top corner. The net ripples, and the stadium erupts in a symphony of cheers. The combination of ");
            say(<Player1>);
            say("'s vision, ");
            say(<Player2>);
            say("'s precision, and ");
            say(<Player3>);
            say("'s acrobatics has produced a goal for the ages. A true masterpiece on the grand canvas of football, and the fans won't forget this moment of brilliance anytime soon!");
            break;
        case 1:
            say("Get ready to witness a moment of pure magic on the pitch! As ");
            say(<team1>);
            say(" surges forward in attack, it's the dynamic ");
            say(<player1>);
            say(" who seizes the spotlight. The ball finds its way to ");
            say(<player1>);
            say(" just outside the penalty area, and the crowd can sense something extraordinary is about to unfold.\nWith a burst of skill, ");
            say(<player1>);
            say(" gracefully maneuvers past a defender, creating space for the perfect shot. The stadium holds its collective breath as ");
            say(<player1>);
            say(" winds up and unleashes an absolute thunderbolt from distance! The ball catapults off ");
            say(<player1>);
            say("'s boot, leaving a trail of excitement in its wake.\nThe goalkeeper");
            say(<Goalkeeper>);
            say(" is left rooted to the spot, helpless against the sheer power and precision of ");
            say(<player1>);
            say("'s strike. The net bulges, and the crowd erupts in a chorus of cheers as ");
            say(<team1>);
            say(" celebrates a goal for the ages. ");
            say(<player1>);
            say("'s goal from outside the penalty area is not just a display of skill; it's a masterpiece, etching its place in the annals of football brilliance. What a sensational moment on the field!");
            break;
        case 2:
            say(<team1>);
            say(" gets the ball as ");
            say(<player1>);
            say("recives the ball , he dribbles the first player with a small touch to the ball ,he runs toward a group of defenders. WHAT IS HE THINKING ABOUT?!! WHAT HE'S GOING TO DO?!! ANKARA ");
            say(<player1>);
            say("!! ANKARA");
            say(<player1>);
            say("!! ANKARA");
            say(<player1>);
            say("!! GOOOAAL!!!!!!! \nunbelievable he manages to get throw all the defenders and scored a beautiful goal .It's a historical goal .That's why he is the goat ,the greatest of all time.");
            break;
    
    }
// counter attack
// team1 scored
//<player1> and <player2> are attackers

    switch (dice)
    {
        case 0:
            say("It's a lightning-fast counter-attack from ");
            say(<team1>);
            say(" reminiscent of Arsenal's style! The ball is won back deep in their own half by ");
            say(<player1>);
            say(", who displays exquisite vision to initiate the break. With a precise long pass, ");
            say(<player1>);
            say(" finds ");
            say(<player2>);
            say(" making a blistering run down the flank.\nAs ");
            say(<player2>);
            say(" advances, ");
            say(<defender1>);
            say(" and ");
            say(<defender2>);
            say(" from ");
            say(<team2>);
            say(" scramble to get back. However, ");
            say(<player2>);
            say("'s pace proves too much to handle. With a burst of speed, ");
            say(<player2>);
            say(" leaves the defenders in the dust, storming into the opposition's final third.\nNow, it's a 2v2 situation! ");
            say(<player2>);
            say(" cleverly draws the attention of both defenders before threading a perfectly timed pass to ");
            say(<player1>);
            say(", who's charging into the box. With composure and precision, ");
            say(<player1>);
            say(" slots the ball past the onrushing goalkeeper. A textbook counter-attack executed flawlessly by ");
            say(<team1>);
            say(".");
            break;
        case 1:
            say(<team1>);
            say(" springs into action with a devastating counter-attack! The play begins with ");
            say(<player1>);
            say("'s interception in their own half. Showing incredible composure, ");
            say(<player1>);
            say(" quickly releases the ball to ");
            say(<player2>);
            say(", who's already on the move towards the opposition goal.\nAs ");
            say(<player2>);
            say(" races forward, ");
            say(<defender1>);
            say(" and ");
            say(<defender2>);
            say(" desperately try to close the gap. But ");
            say(<player2>);
            say("'s pace and ball control are too much to handle. Sensing the danger, ");
            say(<player2>);
            say(" cleverly cuts inside, leaving the defenders trailing.\nWith the defense stretched, ");
            say(<player2>);
            say(" spots the perfectly-timed run of ");
            say(<player1>);
            say(". The ball is delivered with pinpoint accuracy, and ");
            say(<player1>);
            say("makes no mistake in finishing past the goalkeeper. A lightning counter-attack that showcases the devastating speed and precision of ");
            say(<team1>);
            say(".");
            break;
        case 2:
            say("Get ready for a rapid-fire counter-attack from ");
            say(<team1>);
            say(" reminiscent of Arsenal's glory days! The ball is won in their own half by ");
            say(<player1>);
            say(", who wastes no time in initiating the break. A quick, incisive pass from ");
            say(<player1>);
            say(" finds ");
            say(<player2>);
            say(" in acres of space as he exploits the gaps left by ");
            say(<defender1>);
            say(" and ");
            say(<defender2>);
            say(".\nAs ");
            say(<player2>);
            say(" charges forward, the defenders are left scrambling to recover. The sheer speed of ");
            say(<player2>);
            say(" is on full display as he breezes past ");
            say(<defender1>);
            say(" and ");
            say(<defender2>);
            say(", creating a 1v1 opportunity against the goalkeeper.\nWith ice in his veins, ");
            say(<player2>);
            say(" calmly slots the ball into the back of the net. It's a clinical finish that puts an exclamation mark on a breathtaking counter-attack by ");
            say(<team1>);
            say(".");
            break;
    
    }
// defended counter attack

    switch (dice)
    {
        case 0:
            say("An explosive counter-attack from ");
            say(<team1>);
            say(" takes shape! It all begins with a swift interception by ");
            say(<player1>);
            say(" in their own half. With a burst of speed, ");
            say(<player1>);
            say(" charges forward and releases a perfectly timed pass to ");
            say(<player2>);
            say(", who's surging down the wing.\nHowever, the defenders of ");
            say(<team2>);
            say(", ");
            say(<defender1>);
            say(" and ");
            say(<defender2>);
            say(", showcase resilience and determination. They track back with impressive speed, closing down the space and cutting off ");
            say(<player2>);
            say("'s path. In a crucial defensive effort, ");
            say(<defender1>);
            say(" intercepts the final pass, thwarting ");
            say(<team1>);
            say("'s attempt and extinguishing the threat.");
            break;
        case 1:
            say(<team1>);
            say(" initiates a rapid counter-attack, with ");
            say(<player1>);
            say(" leading the charge! After winning the ball in their own half, ");
            say(<player1>);
            say(" releases a swift through ball to ");
            say(<player2>);
            say(", who's breaking forward with intent.\nYet, the defenders of ");
            say(<team2>);
            say(", ");
            say(<defender1>);
            say(" and ");
            say(<defender2>);
            say(", display exceptional defensive awareness. They quickly close in on ");
            say(<player2>);
            say(", forming a resilient defensive duo. ");
            say(<defender1>);
            say(" makes a perfectly-timed interception, denying ");
            say(<team1>);
            say(" access to the danger zone and halting the counter-attack.");
            break;
        case 2:
            say("An ambitious counter-attack unfolds for ");
            say(<team1>);
            say(", triggered by ");
            say(<player1>);
            say("'s interception. With a burst of pace, ");
            say(<player1>);
            say(" delivers a piercing pass to ");
            say(<player2>);
            say(", who's sprinting into open space.\nThe defenders of ");
            say(<team2>);
            say(", ");
            say(<defender1>);
            say(" and ");
            say(<defender2>);
            say(", showcase solid defensive organization. They communicate effectively, closing down passing lanes and nullifying the threat. As ");
            say(<player2>);
            say(" attempts to break through, ");
            say(<defender2>);
            say(" steps in with a crucial tackle, extinguishing the counter-attack and regaining possession for ");
            say(<team2>);
            say(".");
            break;
    
    }

    // counter attack clutched by the goalkeeper

    switch (dice)
    {
        case 0:
            say(<team1>);
            say(" launches a rapid counter-attack, sparked by ");
            say(<player1>);
            say("'s interception in their own half. ");
            say(<player1>);
            say(" quickly releases the ball to ");
            say(<player2>);
            say(", who's streaking down the field with purpose.\nHowever, the goalkeeper of ");
            say(<team2>);
            say(" is up to the challenge.");
            say(<player2>);
            say(" approaches the penalty area and takes a powerful shot, but the goalkeeper reacts brilliantly, making a crucial save. The counter-attack is thwarted, and ");
            say(<team2>);
            say(" breathes a sigh of relief as they retain control of the situation.");
            break;
        case 1:
            say("A lightning-quick counter-attack is set in motion by ");
            say(<team1>);
            say(", led by the industrious ");
            say(<player1>);
            say(". After winning the ball in their own half, ");
            say(<player1>);
            say(" initiates a swift transition, finding ");
            say(<player2>);
            say(" in space.\nYet, the goalkeeper of ");
            say(<team2>);
            say(" proves to be a formidable obstacle. As ");
            say(<player2>);
            say(" unleashes a fierce shot from outside the box, the goalkeeper makes a diving save, denying ");
            say(<team1>);
            say(" the opportunity to convert the counter-attack into a goal. A moment of heroics from the goalkeeper preserves the scoreline for ");
            say(<team2>);
            say(".");
            break;
        case 2:
            say(<team1>);
            say(" embarks on a counter-attack fueled by the dynamism of ");
            say(<player1>);
            say(". Intercepting the ball in their own half, ");
            say(<player1>);
            say(" quickly distributes it to ");
            say(<player2>);
            say(", who makes a determined run towards goal.\nBut the goalkeeper of ");
            say(<team2>);
            say(" is on high alert. As ");
            say(<player2>);
            say(" approaches the penalty area and takes aim, the goalkeeper anticipates the shot and makes a spectacular diving save. The counter-attack is neutralized, showcasing the shot-stopping prowess of ");
            say(<team2>);
            say("'s goalkeeper.");
            break;
    
    }

    // defended attack

    switch (dice)
    {
        case 0:
            say("Here comes a spellbinding attack from ");
            say(<team1>);
            say(" as they weave their way into the opponent's half! The play is ignited by the creative genius of ");
            say(<Player1>);
            say(", who orchestrates the movement with a perfectly weighted through ball. ");
            say(<Player2>);
            say(" latches onto it, displaying impeccable control and pace, tearing through the defensive lines of ");
            say(<team2>);
            say(".\nAs ");
            say(<Player2>);
            say(" reaches the edge of the box, ");
            say(<defender1>);
            say(", ");
            say(<defender2>);
            say(", and ");
            say(<defender3>);
            say(" from ");
            say(<team2>);
            say(" respond with resolute defending. Like a fortress, they close in on ");
            say(<Player2>);
            say(", denying any space for a shot. In a quick exchange of passes, ");
            say(<Player3>);
            say(" attempts to create an opening, but the trio of defenders stands firm.\nThe defensive trio of ");
            say(<team2>);
            say(" showcases remarkable teamwork, with ");
            say(<defender1>);
            say(" making a crucial interception. With synchronized precision, ");
            say(<defender2>);
            say(" and ");
            say(<defender3>);
            say(" provide additional cover, thwarting ");
            say(<team1>);
            say("'s attacking intent. The ball is swiftly cleared back to the center of the field, highlighting the cohesive defensive efforts of ");
            say(<team2>);
            say(" and their ability to withstand a formidable ");
            say(<team1>);
            say(" attack.");
            break;
        case 1:
            say("Buckle up for a thrilling attacking display from ");
            say(<team1>);
            say(" as they march forward with purpose! The maestro ");
            say(<Player1>);
            say(" sparks the movement with a sublime pass, setting the dynamic ");
            say(<Player2>);
            say(" in motion. ");
            say(<Player2>);
            say(" storms down the field, showcasing blistering pace.\nHowever, the defenders of ");
            say(<team2>);
            say(", including the formidable trio ");
            say(<defender1>);
            say(", ");
            say(<defender2>);
            say(", and ");
            say(<defender3>);
            say(", prove their mettle not only as a cohesive unit but also as individual performers. ");
            say(<defender1>);
            say(" anticipates ");
            say(<Player2>);
            say("'s next move, executing a brilliant challenge that disrupts the attack.\nUndeterred, ");
            say(<defender2>);
            say(" seizes the opportunity, making a decisive interception. With tactical awareness, ");
            say(<defender2>);
            say(" navigates through the opposition, initiating a counter-attack of their own. The crowd is treated to a display of defensive skill, as ");
            say(<defender3>);
            say(" joins the fray, repelling ");
            say(<team1>);
            say("'s threat and sending the ball back to the center of the field.");
            break;
        case 2:
            say("Get ready for an attacking spectacle from ");
            say(<team1>);
            say(" as they navigate the opposition half! The play begins with the visionary ");
            say(<Player1>);
            say(", orchestrating the movement with a perfectly placed pass, unleashing the pace of ");
            say(<Player2>);
            say(". ");
            say(<Player2>);
            say("surges forward, eyes set on goal.\nYet, the defenders of ");
            say(<team2>);
            say(" are not just a united force; they are skilled contributors. Witness the artistry of ");
            say(<defender1>);
            say(", who times a challenge to perfection, dispossessing ");
            say(<Player2>);
            say(" and halting the attack in its tracks.\nNot to be outdone, ");
            say(<defender2>);
            say(" seizes the moment, executing a decisive interception. With tactical awareness, ");
            say(<defender2>);
            say(" adeptly navigates through opposition players, disrupting ");
            say(<team1>);
            say("'s rhythm. Displaying a commendable sense of control, ");
            say(<defender2>);
            say(" efficiently clears the ball back to the midfield, nullifying ");
            say(<team1>);
            say("'s threat and restoring order for ");
            say(<team2>);
            say(".");
            break;
    
    }


   
    return 0;
}



void red () {
  printf("\033[1;31m");
}

void yellow {
  printf("\033[1;33m");
}

void reset () {
  printf("\033[0m");
}