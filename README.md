# Two-player-Tetris
  借用经典游戏《俄罗斯方块》的游戏规则，基于SFML引擎进行，对《俄罗斯方块》 游戏加装了多人功能。
游戏平台类承载Tetris对象，扮演的是调度管理游戏资源的角色。平台类中包含两个Tetris类的实例对象player1和player2；
在游戏中增加一个方块图形的生成缓冲区--Next区，让玩家能够事先知道下一个方块是哪个图形。
①增设Next区，随机存储玩家的下一个方块图形；
②当方块碰撞着地后，用Next区的方块图形对新方块进行赋值，即新产生的方块来自Next区；
③当Next区的方块图形被提取，则在Next区随机生成下一个方块图形；

在生成模块中引入Bag7的思想：即取7个基本图形各1个打包成Bag，每次从Bag中随机提出1个图形，当一个Bag中的图形全部被取出，则重新生成下一
个Bag包，以此确保每14个方块图形中，各图形至少出现1次（该算法能确保连续14个图形，至少包含1个完整的Bag包）；
实现了数据交换，玩家可以通过Hold功能将自己暂时不需要的图形方块存放在Hold区，在需要的时候再通过Hold功能交换出来使用；
对各种wall kick现象进行了修复；
实现了图形方块的速降、缓冲以及投影功能；
漂亮的消行奖励动画特效。
