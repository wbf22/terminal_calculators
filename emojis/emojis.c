
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>


/*

valgrind --leak-check=full --show-leak-kinds=all ./ti

leaks -atExit -- ./ti test/wizards.jpg


*/

char* RESET = "\033[0m";
char* RED = "\033[252;3;3m";
char* YELLOW = "\033[252;186;3m";

void extract_emojis_from_txt() {
    FILE *file = fopen("emojis_src.txt", "r"); // open for reading
    FILE *out = fopen("emojis.txt", "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[256]; // buffer to hold each line
    while (fgets(line, sizeof(line), file)) {
        // find '(' and ')'
        char *start = strchr(line, '(');
        char *end = strchr(line, ')');

        if (start && end && end > start) {
            // calculate length of emoji substring
            size_t len = end - start - 1;

            if (len > 0 && len < sizeof(line)) {
                char emoji[64] = {0};
                strncpy(emoji, start + 1, len);
                emoji[len] = '\0';
                fprintf(out, " %s", emoji);
            }
        }
    }
    fprintf(out, "\n");

    fclose(file);
    fclose(out);
}


void print_emoji_group(int window_width, char* str) {

    int planned_width = window_width; // most emojis take 2 spaces
    int len = strlen(str); 
    int line_l = 0;
    for(int i = 0; i < len; ++i) {
        printf("%c", str[i]);
        ++line_l;

        if (
            str[i] == ' ' && 
            line_l > planned_width
        ) {
            line_l = 0;
            printf("\n");
        }
    }
    printf("\n\n");


}


int main(int argc, char **argv) {
    if (argc > 1) {
        char* flag = argv[1];
        if (strcmp(flag, "-h") == 0 || strcmp(flag, "--help") == 0) {
            printf("-c -> print common emojis only\n");
        }
        
    }

    // extract_emojis_from_txt();
    setbuf(stdout, NULL); // disable buffering for stdout
    /*
    

    
    */

    // get terminal dimensions
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl");
        return 1;
    }
    int width = w.ws_col;
    int height = w.ws_row;

    // flags
    print_emoji_group(width, "🇦🇨 🇦🇩 🇦🇪 🇦🇫 🇦🇬 🇦🇮 🇦🇱 🇦🇲 🇦🇴 🇦🇶 🇦🇷 🇦🇸 🇦🇹 🇦🇺 🇦🇼 🇦🇽 🇦🇿 🇧🇦 🇧🇧 🇧🇩 🇧🇪 🇧🇫 🇧🇬 🇧🇭 🇧🇮 🇧🇯 🇧🇱 🇧🇲 🇧🇳 🇧🇴 🇧🇶 🇧🇷 🇧🇸 🇧🇹 🇧🇻 🇧🇼 🇧🇾 🇧🇿 🇨🇦 🇨🇨 🇨🇩 🇨🇫 🇨🇬 🇨🇭 🇨🇮 🇨🇰 🇨🇱 🇨🇲 🇨🇳 🇨🇴 🇨🇵 🇨🇷 🇨🇺 🇨🇻 🇨🇼 🇨🇽 🇨🇾 🇨🇿 🇩🇪 🇩🇬 🇩🇯 🇩🇰 🇩🇲 🇩🇴 🇩🇿 🇪🇦 🇪🇨 🇪🇪 🇪🇬 🇪🇭 🇪🇷 🇪🇸 🇪🇹 🇪🇺 🇫🇮 🇫🇯 🇫🇰 🇫🇲 🇫🇴 🇫🇷 🇬🇦 🇬🇧 🇬🇩 🇬🇪 🇬🇫 🇬🇬 🇬🇭 🇬🇮 🇬🇱 🇬🇲 🇬🇳 🇬🇵 🇬🇶 🇬🇷 🇬🇸 🇬🇹 🇬🇺 🇬🇼 🇬🇾 🇭🇰 🇭🇲 🇭🇳 🇭🇷 🇭🇹 🇭🇺 🇮🇨 🇮🇩 🇮🇪 🇮🇱 🇮🇲 🇮🇳 🇮🇴 🇮🇶 🇮🇷 🇮🇸 🇮🇹 🇯🇪 🇯🇲 🇯🇴 🇯🇵 🇰🇪 🇰🇬 🇰🇭 🇰🇮 🇰🇲 🇰🇳 🇰🇵 🇰🇷 🇰🇼 🇰🇾 🇰🇿 🇱🇦 🇱🇧 🇱🇨 🇱🇮 🇱🇰 🇱🇷 🇱🇸 🇱🇹 🇱🇺 🇱🇻 🇱🇾 🇲🇦 🇲🇨 🇲🇩 🇲🇪 🇲🇫 🇲🇬 🇲🇭 🇲🇰 🇲🇱 🇲🇲 🇲🇳 🇲🇴 🇲🇵 🇲🇶 🇲🇷 🇲🇸 🇲🇹 🇲🇺 🇲🇻 🇲🇼 🇲🇽 🇲🇾 🇲🇿 🇳🇦 🇳🇨 🇳🇪 🇳🇫 🇳🇬 🇳🇮 🇳🇱 🇳🇴 🇳🇵 🇳🇷 🇳🇺 🇳🇿 🇴🇲 🇵🇦 🇵🇪 🇵🇫 🇵🇬 🇵🇭 🇵🇰 🇵🇱 🇵🇲 🇵🇳 🇵🇷 🇵🇸 🇵🇹 🇵🇼 🇵🇾 🇶🇦 🇷🇪 🇷🇴 🇷🇸 🇷🇺 🇷🇼 🇸🇦 🇸🇧 🇸🇨 🇸🇩 🇸🇪 🇸🇬 🇸🇭 🇸🇮 🇸🇯 🇸🇰 🇸🇱 🇸🇲 🇸🇳 🇸🇴 🇸🇷 🇸🇸 🇸🇹 🇸🇻 🇸🇽 🇸🇾 🇸🇿 🇹🇦 🇹🇨 🇹🇩 🇹🇫 🇹🇬 🇹🇭 🇹🇯 🇹🇰 🇹🇱 🇹🇲 🇹🇳 🇹🇴 🇹🇷 🇹🇹 🇹🇻 🇹🇼 🇹🇿 🇺🇦 🇺🇬 🇺🇲 🇺🇸 🇺🇾 🇺🇿 🇻🇦 🇻🇨 🇻🇪 🇻🇬 🇻🇮 🇻🇳 🇻🇺 🇼🇫 🇼🇸 🇽🇰 🇾🇪 🇾🇹 🇿🇦 🇿🇲 🇿🇼 ");

    // phone numbers
    print_emoji_group(width, "#⃣ *⃣ 0⃣ 1⃣ 2⃣ 3⃣ 4⃣ 5⃣ 6⃣ 7⃣ 8⃣ 9⃣ ");
    

    // symbols
    print_emoji_group(width, "⭐ ⭕ ❓ ❔ ❕ ❗ ‼️ ➕ ➖ ➗ ➰ ➿ © ® ‼ ⁉ ™ ℹ ↔ ↕ ↖ ↗ ↘ ↙ ↩ ↪ ⌨ ⏏ ⏭ ⏮ ⏯ ⏱ ⏲ ⏸ ⏹ ⏺ Ⓜ ▪ ▫ ▶ ◀ ◻ ◼ ◽ ◾ ☀ ☁ ☂ ☃ ☄ ☎ ☑ ☔ ☕ ☘ ☝ ☠ ☢ ☣ ☦ ☪ ☮ ☯ ☸ ☹ ☺ ♈ ♉ ♊ ♋ ♌ ♍ ♎ ♏ ♐ ♑ ♒ ♓ ♠ ♣ ♥ ♦ ♨ ♻ ♿ ⚒ ⚓ ⚔ ⚖ ⚗ ⚙ ⚛ ⚜ ⚠ ⚡ ✌ ✍ ✏ ✒ ✔ ✖ ✝ ✡ ⛈ ⛏ ⛑ ⛓ ⚰ ⚱ ⛩ ⛰ ⛱ ⛴ ⛷ ⛸ ✂ ✈ ✉ ✳ ✴ ❄ ❇ ❣ ❤ ➡ 〰 〽 ");

    // asian symbols
    print_emoji_group(width, "🈂 🈚 🈯 🈲 🈳 🈴 🈵 🈶 🈷 🈸 🈹 🈺 🉐 🉑 ㊗ ㊙ 🀄 ");

    // random junk
    print_emoji_group(width, "🅰 🅱 🅾 🅿 🆎 🆑 🆒 🆓 🆔 🆕 🆖 🆗 🆘 🆙 🆚 🈁 🔘 🔞 🔟 🔠 🔡 🔢 🔣 🔤 🚾 ⛎  🏻 🏼 🏽 🏾 🏿 ");
    
    // signs
    print_emoji_group(width, "🚸 🚹 🚺 🚻 🚼 📳 📴 🛂 🛃 🛄 🛅 👪 ⛔ 🏧 🚫 🚭 🚮 🚯 🚱 🚳 🚷 🛐 💮 ");

    // pictures
    print_emoji_group(width, "🌁 🌃 🌄 🌅 🌆 🌇 🌉 🌌 🌠 🎆 🎇 🗾 🛣 🛤 🏞 ");

    // controls
    print_emoji_group(width, "🔙 🔚 🔛 🔜 🔝 ⏩ ⏪ ⏫ ⏬ 🔀 🔁 🔂 🔃 🔄 📶 🎦 🔼 🔽 ⤴ ⤵ ⬅ ⬆ ⬇ 🔅 🔆 🔇 🔈 🔉 🔊 ✅ ❌ ❎ ⬛ ⬜ ⚪ ⚫ ");

    // buildings
    print_emoji_group(width, "🏘 🏙 🏚 🏛 🏟 🏠 🏡 🏢 🏣 🏤 🏥 🏦 🏨 🏩 🏪 🏫 🏬 🏭 ⛪ 🏯 🏰 🏗 ");

    // time
    print_emoji_group(width, "⌚ ⌛ ⏳ ⏰ 🕐 🕑 🕒 🕓 🕔 🕕 🕖 🕗 🕘 🕙 🕚 🕛 🕜 🕝 🕞 🕟 🕠 🕡 🕢 🕣 🕤 🕥 🕦 🕧 🕰 🏮 ");

    // weather
    print_emoji_group(width, "🌡 🌤 🌥 🌦 🌧 🌨 🌩 ⛈️ 🌪 🌫 🌬 ⛅ ☀️ ");

    // plants
    print_emoji_group(width, "🌰 🌱 🌲 🌳 🌴 🌵 🌶 🌷 🌸 🌹 🌺 🌻 🌼 🌽 🌾 🌿 🍀 🍁 🍂 🍃 🍄 🏵 ");

    // space and geology
    print_emoji_group(width, "🌍 🌎 🌏 🌐 🌑 🌒 🌓 🌔 🌕 🌖 🌗 🌘 🌙 🌚 🌛 🌜 🌝 🌞 🌟 🛰 🏔 🌊 🌋 💫 🏜 🏝 📡 ");

    // objects
    print_emoji_group(width, "⚽ ⚾ 🎾 🏀 🎱 🏈 🏉 🏏 🏐 🏑 🏒 🏸 🏹 🏓 🏅 🏆 🌂 🎀 🎁 🎈 🎉 🎊 🎋 🎌 🎍 🎎 🎏 🎐 🎑 🎒 🎓 🎖 🎗 🎙 🎚 🎛 🎞 🎟 🎠 🎡 🎢 🎣 🎤 🎥 🎧 🎨 🎩 🎪 🎫 🎬 🎭 🎮 🎯 🎰 🎲 🎳 🎴 🎵 🎶 🎷 🎸 🎹 🎺 🎻 🎼 🎽 🎿 🏁 💰 💱 💲 💳 💴 💵 💶 💷 💸 💹 💺 💻 💼 💽 💾 💿 📀 📁 📂 📃 📄 📅 📆 📇 📈 📉 📊 📋 📌 📍 📎 📏 📐 📑 📒 📓 📔 📕 📖 📗 📘 📙 📚 📛 📜 📝 📞 📟 📠 📢 📣 📤 📥 📦 📧 📨 📩 📪 📫 📬 📭 📮 📯 📰 📱 📲 📵 📷 📸 📹 📺 📻 📼 📽 📿 🔋 🔌 🔍 🔎 🔏 🔐 🔑 🔒 🔓 🔔 🔕 🔖 🔗 🔦 🔧 🔨 🔩 🔪 🔫 🔬 🔭 🔮 🔯 🔰 🔱 🔲 🔳 🔴 🔵 🔶 🔷 🔸 🔹 🔺 🔻 🕉 🕊 🕋 🕌 🕍 🕎 🕳 🕴 🕵 🕶 🕷 🕸 🕹 🖇 🖊 🖋 🖌 🖍 👓 👔 👕 👖 👗 👘 👙 👚 👛 👜 👝 👞 👟 👠 👡 👢 👑 👒 🖥 🖨 🖱 🖲 🖼 🗂 🗃 🗄 🗑 🗒 🗓 🗜 🗝 🗞 🗡 🗣 🗯 🗳 🗺 🗻 🗼 🗽 💈 💉 💊 🚬 🗿 🚥 🚦 🚧 🚨 🚩 🚪 🚰 🚽 🚿 🛀 🛁 🛋 🛌 🛍 🛎 🛏 🛠 🛡 🛢 💄 💅 💎 💠 💡 🃏 🏷 🏺 ⛄ ⛲ ⛳ ⛵ ⛺ ⛽ 🎃 🎄 🏕 🏖 🕯 🏳 🏴 💣 ");

    // vehicles
    print_emoji_group(width, "🚀 🚁 🚂 🚃 🚄 🚅 🚆 🚇 🚈 🚉 🚊 🚋 🚌 🚍 🚎 🚏 🚐 🚑 🚒 🚓 🚔 🚕 🚖 🚗 🚘 🚙 🚚 🚛 🚜 🚝 🚞 🚟 🚠 🚡 🚢 🚣 🚤 🚲 🛥 🛩 🛫 🛬 🛳 🏍 🏎 ");

    // animals
    print_emoji_group(width, "🐀 🐁 🐂 🐃 🐄 🐅 🐆 🐇 🐈 🐉 🐊 🐋 🐌 🐍 🐎 🐏 🐐 🐑 🐒 🐓 🐔 🐕 🐖 🐗 🐘 🐙 🐚 🐛 🐜 🐝 🐞 🐟 🐠 🐡 🐢 🐣 🐤 🐥 🐦 🐧 🐨 🐩 🐪 🐫 🐬 🐭 🐮 🐯 🐰 🐱 🐲 🐳 🐴 🐵 🐶 🐷 🐸 🐹 🐺 🐻 🐼 🐽 🐾 🐿 🦀 🦁 🦂 🦃 🦄 🦇 🦔 🦖 ");

    // food 
    print_emoji_group(width, "🌭 🌮 🌯 🍅 🍆 🍇 🍈 🍉 🍊 🍋 🍌 🍍 🍎 🍏 🍐 🍑 🍒 🍓 🍔 🍕 🍖 🍗 🍘 🍙 🍚 🍛 🍜 🍝 🍞 🍟 🍠 🍡 🍢 🍣 🍤 🍥 🍦 🍧 🍨 🍩 🍪 🍫 🍬 🍭 🍮 🍯 🍰 🍱 🍲 🍳 🍴 🍵 🍶 🍷 🍸 🍹 🍺 🍻 🍼 🍽 🍾 🍿 🎂 🧀 🥐 ");

    // effects
    print_emoji_group(width, "✨ 🔥 🌈 🌀 💬 💭 💥 💦 💧 💨 💤 💯 💢 ");

    // love
    print_emoji_group(width, "❤️ ♥️ 💏 💐 💑 💒 💓 💔 💕 💖 💗 💘 💙 💚 💛 💜 🖤 💝 💞 💟 💋 💌 💍 ❣️ ");

    // people
    print_emoji_group(width, "👤 👥 👦 👧 👨 👩 👫 👬 👭 👮 👯 👰 👱 👲 👳 👴 👵 👶 👷 👸 🙅 🙆 🙇 🙈 🙉 🙊 🙋 🙌 🙍 🙎 🎅 🏂 🏃 🏄 🏇 🏊 🏋 🏌 💁 💂 💃 🚴 🚵 🚶 💆 💇 ⛹ 👣 🤦 🤷 🙆 🕺 ");

    // hand signals
    print_emoji_group(width, "👆 👇 👈 👉 👊 👋 👌 👍 👎 👏 👐 ✊ ✋ 🖐 🖕 🖖 🤘 ✌️ ");

    // faces
    print_emoji_group(width, "😀 😁 😂 🤣 😃 😄 😅 😆 😇 😈 😉 😊 😋 😌 😍 😎 😏 😐 😑 😒 😓 😔 😕 😖 😗 😘 😙 😚 😛 😜 😝 😞 😟 😠 😡 😢 😣 😤 😥 😦 😧 😨 😩 😪 😫 😬 😭 😮 😯 😰 😱 😲 😳 😴 😵 😶 😷 😸 😹 😺 😻 😼 😽 😾 😿 🙀 🙁 🙂 🙃 🙄 👹 👺 👻 👼 👽 👾 👿 💀 🤐 🤑 🤒 🤓 🤔 🤕 🤖 🤗 👄 👅 👁 👂 👃 👀 🙏 💪 💩 ☺️ 🤩 🤭 🤪 🤤 🐦 🤡 ");

    // common
    print_emoji_group(width, "😂 ❤️ 🤣 😍 😊 🙏 💕 😭 😘 👍 😅 👏 😁 ♥️ 🔥 💔 💖 💙 😢 🤔 😆 🙄 💪 😉 ☺️ 👌 🤗 💜 😔 😎 😇 🌹 🤦 🎉 ‼️ 💞 ✌️ ✨ 🤷 😱 😌 🌸 🙌 😋 💗 💚 😏 💛 🙂 💓 🤩 😄 😀 🖤 😃 💯 🙈 👇 🎶 😒 🤭 ❣️ ❗ 😜 💋 👀 😪 😑 💥 🙋 😞 😩 😡 🤪 👊 ☀️ 😥 🤤 👉 💃 😳 ✋ 😚 😝 😴 🌟 😬 🙃 🍀 🌷 😻 😓 ⭐ ✅ 🌈 😈 🤘 ");

    // favorites
    print_emoji_group(width, "😂 😍 😊 💃 😥 🙆 😅 🎉 💔 😎 🤷 🤔 ✨ 🔥 💀 🕺 🤓 👍 🤦 © ® ⛄ 🌎 👺 🌝 🌈 💯 👽 🚽 💩 💪 🚀 🤡 🦀 🦄 💣 😏 🇺🇸 🇳🇮 ");

    return 0;
}
