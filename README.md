# The Infernal Tunnels
## Giới thiệu bản thân
- Họ và tên: Nguyễn Thành Minh.
- Mã sinh viên: 23020684.
- Lớp: K68J.
- Bài tập lớn: The Infernal Tunnels / INT2215_52 - Môn: Lập trình nâng cao.

## Video trải nghiệm game và trình bày qua về code
- Link youtube: **https://youtu.be/vQ2LoA7_kTo**

## Cách tải game
### Cách 1: Không bao gồm code
Tải game (được nén thành .zip) tại link sau: **https://github.com/MinhTNuet/TheInfernalTunnels/releases/tag/publised**.
Cách này tiết kiệm bộ nhớ và thời gian tải đi rất nhiều (khoảng 103MB).
Giải nén game vào một thư mục và bật TheInfernalTunnels.exe lên và chơi.

### Cách 2: Bao gồm code và có thể biên dịch
Bước 1: Clone repo này về hoặc chọn Code -> Download Zip.
- Tất cả code đều nằm trong thư mục src.
- Có thể nhảy đến bước 5 để chơi luôn
Bước 2: Cài mingw. Ở đây tôi cài đặt phiên bản MinGW-W64 GCC-8.1. **x86_64-posix-seh**
Một số chú ý:
- Nếu sử dụng trình biên dịch khác thì phải dịch lại icon: vào thư mục icon rồi dùng lệnh windres main.rc -O coff main.res trong cmd.
- Phải xóa ba dll của c++ trong thư mục chứa pvz.exe: libgcc_s_seh-1.dll, libstdc++-6.dll, libwinpthread-1.dll. Ba dll này chỉ dành cho người chơi không cài sẵn c++ trong máy.
Bước 3: Cài GNU make.
Bước 4: Mở cmd trong thư mục chứa Makefile và gõ lệnh make.
Bước 5: Bật TheInfernalTunnels.exe và chơi game.

## Giới thiệu về game
### Cốt truyện
- Người chơi sẽ vào vai một nhân vật phù thủy sở hữu sức mạnh hắc ám cực kì mạnh mẽ nhưng anh ta vô cùng tốt bụng.
- Vào một ngày, ở trên những vùng đất hoang xuất hiện những lăng mộ, hầm ngục vô tận và tăm tối.
- Đừng để vẻ ngoài đáng yêu của những con quái trong hầm đánh lừa, khi chúng ta tới gần và mất cảnh giác, chúng có thể giết ta mà không kịp trở tay.
- Nhiệm vụ của anh phù thủy là tiêu diệt những con quái vật đó để dành lại tự do, bình yên cho người dân.
- Mặc dù khó khăn, gian nan nhưng liệu nhân vật chính của chúng ta có thể thành công không? Hãy cùng đón xem nhé!

### Luật chơi
- Người chơi sẽ chỉ có 3 hp. Nên phải thực sự rất cẩn thận khi đánh nhau với các con quái và cũng thực sự cẩn thận với những cái hố vì những điều bất ngờ sẽ đến cuối cùng.
- Hiện trong game mới chỉ có 2 loại quái vật(nếu có thêm thời gian có thể update thêm nhiều con nữa):
> ![SlimeMonster](SlimeMonster.png): Có khả năng đánh player và mất 1 hp | Khi tiêu diệt thì nhận thêm 1 hp(Nếu đã mất hp trước đó) và nhận 5 score.
> ![PenguinMonster](PenguinMonster.png): Có khả năng đánh player và mất 1 hp | KHi tiêu diệt thì nhận thêm 30 score.
- Bạn cũng có thể chọn cách không giết quái và chỉ chạy vì score sẽ được tăng với mỗi bước chạy theo phương x của bạn(lưu ý: không tính bước đi lại).
- Game sẽ chỉ có 1 phút để các bạn chơi và dành số điểm. Khi hết time có nghĩa là bạn cũng sẽ die và end game.
- Nút di chuyển của player: A(di chuyển sang trái), W(nhảy lên trên), D(di chuyển sang phải) và lưu ý đừng di chuyển liên tục hai nút A và D cùng lúc nhiều lần.
- Hãy đặt ra một chiến thuật hợp lí để có thể đạt được những kỉ lục mới nhé!

### Kỹ thuật đã được sử dụng
- Đọc được file vàxây dựng được các tile map với ứng dụng Tiled.
- Xử lý được va chạm giữa player, monster và wall.
- Đọc và xử lí âm thanh của player và các phím nút, âm thanh của game.
- Biết cách để nối các map đã được tạo từ Tiled.
- Các con quái có thể tự động di chuyển và đuổi theo player khi đến gần và tấn công khi người chơi ở sát.
- Áp dụng được phương pháp tính lerp để camera khi đi theo player được mượt mà hơn.

### Tính năng trong game
- Em đã cài đặt các nút: Play(vào chơi game), Back(Out ra khỏi chương trình game), Restart(chơi lại).
- Khi vào màn hình chính chơi game, sẽ có thanh hp, score hiện tại và highscore, thời gian đếm ngược.
- Khi bị quái đánh hết hp hoặc rơi xuống hố hoặc hết time, player sẽ chết và hiện ra số điểm đã đạt được và nút Restart.
- Nếu đạt được số điểm cao hơn highscore hiện tại sẽ được set lại score = highscore.

## Đồ họa game
- Tileset, background, asset monster và player, em đều lấy từ web này: **https://itch.io/game-assets/free**
- Tileset: **https://miguelsgp.itch.io/free-tileset-dungeon**
- Background: Em tạo qua canva: **https://www.canva.com/**
- Asset monster: **https://free-game-assets.itch.io/free-tiny-hero-sprites-pixel-art**
- Asset player: **https://luizmelo.itch.io/evil-wizard-2**

### Mã nguồn tham khảo
- Lazyfoo: **https://lazyfoo.net/tutorials/SDL/**

## Kết luận
- Đây là thành quả sau hơn 1 tháng đi tiếp thu kiến thức và tham khảo các bài làm trên youtube, web, từ mọi người kể cả bên java, python,...
- Em tự nhận thấy là game có mở bài, thân bài và kết bài.
- Chắc chắn là khi mọi người test game sẽ xuất hiện thêm những bug mới nhưng em mong các thầy có thể châm chước và chấm điểm tốt cho em ạ!
- Đây sẽ là động lực, bước đệm để em có những bước phát triển tốt hơn trong sự nghiệp tương lai!

# EM XIN CẢM ƠN Ạ!!!
