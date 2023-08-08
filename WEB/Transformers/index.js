/*
## Задание 5.2 - Трансформеры и ООП

1. Создать класс `Transformer` со свойствами и методами:
    - `name` 
    - `health` - по умолчанию имеет значение 100
    - `attack()` - будет в дальнейшем переопределен
    - `hit(weapon)` - метод, который обрабытывает логику атаки на данного трансформера, принимает на вход экземпляр класса `Weapon`, отнимает текущее здоровье трансформера на размер атаки (свойство `damage` и `Weapon`).
2. Создать класс `Autobot`, который наследуется от класса `Transformer`.
    - Имеет свойсто `weapon` (экземпляр класса `Weapon`), т.к. автоботы сражаются с использованием оружия.
    - Конструктор класса принимает 2 параметра: имя трансформера и оружее (экземпляр класса `Weapon`). 
    - Метод `attack` возвращает результат использования оружия `weapon.fight()`
3. Создать класс `Deceptikon` который наследуется от класса `Transformer`.
    - Десептиконы не пользуются оружием, поэтому у них нет свойства `weapon`. За то они могут иметь разное количество здоровья.
    - Конструктор класса принимает 2 параметра: имя `name` и количество здоровья `health`
    - Метод `attack` возвращает характеристики стандартного вооружения, например, `{ damage: 5, speed: 1000 }`, где `damage` - это кличество урона, а `speed` - скорость атаки в мс.
4. Создать класс оружия `Weapon`, на вход принимает 2 параметра: `damage` - урон и `speed` - скорость атаки. Имеет 1 метод `fight`, который возвращает характеристики оружия в виде `{ damage: 5, speed: 1000 }`
5. Создать 1 автобота с именем `OptimusPrime` с оружием, имеющим характеристики `{ damage: 100, speed: 1000 }`
6. Создать 1 десептикона с именем `Megatron` и показателем здоровья `10000`
7. Посмотреть что происходит при вызове метода `atack()` у траснформеров разного типа, посмотреть сигнатуры классов
8. Вопрос: сколько нужно автоботов чтобы победить Мегатрона если параметр `speed` в оружии это количество милсекунд до следующего удара? Реализовать симуляцию боя.
*/

// 1. Создать класс `Transformer` со свойствами и методами:
//     - `name` 
//     - `health` - по умолчанию имеет значение 100
//     - `attack()` - будет в дальнейшем переопределен
//     - `hit(weapon)` - метод, который обрабытывает логику атаки на данного трансформера, принимает на вход экземпляр класса `Weapon`, отнимает текущее здоровье трансформера на размер атаки (свойство `damage` и `Weapon`).

//класс - трансформер
class Transformer{
    constructor(name, health = 100){
        this.name = name;
        this.health = health;
    }
    attack() {
    };
    hit(weapon){
        this.health -= weapon.damage;
    }
}
/**
 * 2. Создать класс `Autobot`, который наследуется от класса `Transformer`.
    - Имеет свойсто `weapon` (экземпляр класса `Weapon`), т.к. автоботы сражаются с использованием оружия.
    - Конструктор класса принимает 2 параметра: имя трансформера и оружее (экземпляр класса `Weapon`). 
    - Метод `attack` возвращает результат использования оружия `weapon.fight()`
 */
class Autobot extends Transformer{
    constructor(name, weapon){
        super(name);
        this.weapon = weapon;
    }
    attack(){
        return this.weapon.fight();
    }
}
/**
 * 3. Создать класс `Deceptikon` который наследуется от класса `Transformer`.
    - Десептиконы не пользуются оружием, поэтому у них нет свойства `weapon`. За то они могут иметь разное количество здоровья.
    - Конструктор класса принимает 2 параметра: имя `name` и количество здоровья `health`
    - Метод `attack` возвращает характеристики стандартного вооружения, например, `{ damage: 5, speed: 1000 }`, где `damage` - это кличество урона, а `speed` - скорость атаки в мс.
 */
class Deceptikon extends Transformer{
    constructor(name, health){
        super(name, health);
    }
    attack(){
        return {
            'damage': 5, // урон
            'speed': 1000 // скорость атаки в мс
        }
    }
}
//4. Создать класс оружия `Weapon`, на вход принимает 2 параметра: `damage` - урон и `speed` - скорость атаки. Имеет 1 метод `fight`, который возвращает характеристики оружия в виде `{ damage: 5, speed: 1000 }`

//Класс - оружие
class Weapon{
    constructor( damage, speed){
        this.damage = damage;
        this.speed = speed;
    }
    fight(){
        return {
            'damage': this.damage,
            'speed': this.speed
        }
    }
}

// 5. Создать 1 автобота с именем `OptimusPrime` с оружием, имеющим характеристики `{ damage: 100, speed: 1000 }`

let autobot = new Autobot('OptimusPrime', new Weapon(100, 1000));

// 6. Создать 1 десептикона с именем `Megatron` и показателем здоровья `10000`

let desiptikon = new Deceptikon('Megatron', 10000);

// 7. Посмотреть что происходит при вызове метода `atack()` у траснформеров разного типа, посмотреть сигнатуры классов

console.log(autobot.attack());
console.log(desiptikon.attack());
//возвращаются объекты с одинаковыми ключами, но разными значениями(хотя можно установить и одинаковые)

// 8. Вопрос: сколько нужно автоботов чтобы победить Мегатрона если параметр `speed` в оружии это количество милсекунд до следующего удара? Реализовать симуляцию боя.

const winCountAutobots = () =>{
    const needShootsForKillOneAutobot = autobot.health / desiptikon.attack().damage;
    const needTimeForKillOneAutobot = needShootsForKillOneAutobot * desiptikon.attack().speed;
    
    const damageFromOneAutobot = needTimeForKillOneAutobot / autobot.attack().speed //столько выстрелов сделает автобот
                                 * autobot.attack().damage // такой урон нанесет, за исключением!..
                                 - desiptikon.attack().damage;//Потому что десиптикон атакует первым(ибо он плохой)

    let needAutobotsForWin = 1;

    const summDamage = (countAutobots) =>{
        if(countAutobots === 1){
            return damageFromOneAutobot;
        } else{
            return damageFromOneAutobot * countAutobots + summDamage(countAutobots-1);
        }
    }

    while(summDamage(needAutobotsForWin) < desiptikon.health){
        needAutobotsForWin++;
    }

    return needAutobotsForWin;
}

const needAutobotsForWin = winCountAutobots();
console.log(`for win need ${needAutobotsForWin} autobots`);

//find aren and creation bots
const autobotArena = document.querySelector('.arena-side-1');
const desiptikonArena = document.querySelector('.arena-side-2');
const autobotModel = 
`<div class="bot">
<span>${autobot.health} hp</span>
</div>`;
const desipticonModel = 
`<div class="bot">
<span>${desiptikon.health} hp</span>
</div>`;

//add models on aren
for(let i = 0; i < needAutobotsForWin; i++){
    autobotArena.insertAdjacentHTML('afterbegin',autobotModel);
}
desiptikonArena.insertAdjacentHTML('afterbegin', desipticonModel);
let firstAutobotHealth = autobotArena.firstChild.querySelector('span');//let, потому что первый робот менятся(из-за смерти предыдущего)
const desiptikonHealth = desiptikonArena.firstChild.querySelector('span');

//simulation fight
const autobotsAttack = (autobotCount) =>{
    const summuryDamage = autobot.attack().damage * autobotCount;
    desiptikon.health -= summuryDamage;
    desiptikonHealth.textContent = `${desiptikon.health} hp`;
}
const desiptikonAttack = () =>{
    autobot.health -= desiptikon.attack().damage;
    firstAutobotHealth.textContent = `${autobot.health} hp`
}
const isAutobotDead = () =>{
    return autobot.health <= 0;
}
const isDesiptikonDead = () =>{
    return desiptikon.health <= 0;
}
const clearArenFromDead = () =>{
    if(isAutobotDead()){
        autobot.health = 100;
        if(autobotArena.firstElementChild){//если еще есть автоботы
            autobotArena.firstElementChild.remove();//труп убираем
            firstAutobotHealth = autobotArena.firstChild.querySelector('span');//новую цель атаки десиптикона выбираем
        }
    } else {
        desiptikonArena.firstChild.remove();
    }
}
const desiptikonStep = setInterval(() => {
    desiptikonAttack();

    if(isAutobotDead()){
        clearArenFromDead();
    }
    if(!desiptikonArena.firstChild){
        clearInterval(desiptikonStep);
    }

}, desiptikon.attack().speed/8);//делю для ускорения анимации

const autobotsStep = setInterval(() => {
    const autobotsOnAren = autobotArena.children.length;
    autobotsAttack(autobotsOnAren);

    if(isDesiptikonDead()){
        clearArenFromDead();
        clearInterval(autobotsStep);
        clearInterval(desiptikonStep);
    }
    if(autobotArena.firstChild === null){
        clearInterval(autobotsStep);
    }

}, autobot.attack().speed/8);//делю для ускорения анимации