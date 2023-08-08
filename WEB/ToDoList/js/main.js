/**
 * Задание 1
 * 
 * Вывести реальное время на экран в браузере в формате ЧЧ:ММ:СС. 
 * Должно изменяться каждую секунду.
 */
let clock = document.querySelector('.header__clock');

const watch = () => {
    let time = new Date();
    clock.innerHTML = time.toLocaleTimeString();
    delete time;
}
watch();
setInterval(watch, 1000);
/**
 * Задание 2
 * 
 * Создать список ul>li, написать скрипт который через 5 секунд
 * добавит новый элемент в конце списка и удалит первый элемент списка.
 */
/*----SOLUTION------
const addLi = (ul, text) =>{
    li = document.createElement('li');
    li.textContent = text;
    ul.append(li);
}
const createList = () =>{
    let ul = document.createElement('ul');

    addLi(ul,'smth');
    addLi(ul,'smthsmth');
    addLi(ul,'qwety747');

    return ul;
}
let ul = createList();
document.body.append(ul);

setTimeout(() => {
    ul.firstElementChild.remove();
    addLi(ul,'new element');
}, 5000);
*/
/**
 * Задание 3
 * 
 * Используя JS примените следующие изменения через 3 секунды:
 * - Добавить к 3-ему элементу списка класс line-through который сделает текст
 *   данного элемента зачеркнутым;
 * - Добавить к 2-ему элементу списка аттрибут data-id с значением 2;
 * - Установить галочку 5 пункта в состояние выбрано;
 * - Изменить значение атрибута инпута data-id на "5".
 * 
 * <ul class="list">
 *    <li class="item">Point 1</li>
 *    <li class="item">Point 2</li>
 *    <li class="item">Point 3</li>
 *    <li class="item">Point 4</li>
 *    <li class="item">
 *       <input type="checkbox" data-id="6">Point 5
 *    </li>
 * </ul>
 */
/*---------SOLUTION-----
let ulList = document.querySelector('.list'),
    listChildren = ulList.children;
    
    listChildren[3-1].style.textDecoration = 'line-through';
    listChildren[2-1].setAttribute('data-id', 2);
    listChildren[5-1].firstElementChild.setAttribute('checked');
    listChildren.lastChild.firstElementChild.dataset.id = 5;
    
*/
//  Задание:
//  1. Реализуем приложение Список дел с возможностью добавить новый элемент в список из инпута по нажатию кнопки "Добавить";
//  2. Реализовать удаление элемента по нажатию крестика;
//  3. Реализовать возможность редактирования элемента. 
//   - При нажатии на текст элемента он отображается в инпуте, название кнопки меняется на "Обновить". 
//   - После изменения названия и нажатия на "Обновить" текст элемента изменяется в списке, инпут сбрасывается, кнопка переименовывается обратно в "Добавить". 
//   - Предусмотреть возможность отменить редактирование (крестик в конце инпута), при нажатии на который редактирование прекращается: инпут очищается, кнопка вновь имеет заголовок "Добавить". 
//   - Редактируемый элемент подсвечивается как активный.
//  4. При нажатии на галочку текст итема становится зачеркнутым, при отжатии снова обычным.

let input = document.querySelector('.newTask__pole'),
    addButton = document.querySelector('.newTask__button'),
    //updateButton = document.getElementsByClassName('newTask__button update')[0],
    taskList = document.querySelector('.tasks__list'),
    tasksArray = [];

let exit = document.createElement('button');
exit.classList.add('clear_input');
exit.textContent = 'x';

let updateButton = document.createElement('button');
updateButton.textContent = 'Обновить'
updateButton.classList.add('newTask__button');

if( localStorage.getItem('taskList')){
    tasksArray = JSON.parse(localStorage.getItem('taskList'));
    displayList();
}    

addButton.addEventListener('click', () =>{
    let descrip = input.value;
    if(!descrip.trim()) return;

    let newTask = {
        description: descrip,
        checked: false
    };
    
    tasksArray.push(newTask);
    localStorage.setItem('taskList', JSON.stringify(tasksArray));
    displayList();

    input.value = '';
})

function displayList(){
    let displayList = '';
    tasksArray.forEach((item, index)=>{
        let li = `
        <li class="tasks__task task">
            <input id='item_${index}' class="task__checkbox" ${item.checked ? 'checked': ''} type="checkbox">
            <span for='item_${index}' class="task__text  ${item.checked ? 'checked': ''}">${item.description}</span>
            <button class="task__butt">X</button>
        </li>
        `;
        displayList += li;
    })
    taskList.innerHTML = displayList;
}

taskList.addEventListener('change', (event) =>{

    let id = event.target.getAttribute('id'),
        label = taskList.querySelector(`[for=${id}]`);
        
    
    id = id.replace(/^\D+/g, '');
    
    tasksArray[id].checked = !tasksArray[id].checked;
    label.classList.toggle('checked');
    localStorage.setItem('taskList', JSON.stringify(tasksArray));
})


let choosenTaskForEdit = false,
    whichActive = '';
taskList.addEventListener('click', (event) => {
    let checkbox = span = button = event.target,
        index = button.parentElement.firstElementChild.getAttribute('id').replace(/^\D+/g, '');
        //whichActive = '';

    if(event.target.classList.contains('task__butt')){
        tasksArray.splice(index, 1);
        localStorage.setItem('taskList', JSON.stringify(tasksArray));
        displayList();
    }

    if(event.target.classList.contains('task__text')){
        if(choosenTaskForEdit) return;
        
        choosenTaskForEdit = true;
        
        //делаем спан активным
        span.classList.add('active');
        whichActive = span;

        //создаем кнопку апдейта и прячем старую
        addButton.hidden = true;
        updateButton.hidden = false;
        input.after(updateButton);
        
        //Создаем крестик для инпута в редактировании
        input.after(exit);
        let text = tasksArray[index].description;
        input.value = text;
        
        //при тыкании на крестик 
        exit.addEventListener('click', ()=>{
            input.value = '';
            updateButton.hidden = true;
            addButton.hidden = false;
            whichActive.classList.remove('active');
            choosenTaskForEdit = false;
            exit.remove();
        })

        updateButton.onclick = () =>{
            tasksArray[index].description = input.value;
            localStorage.setItem('taskList', JSON.stringify(tasksArray));

            updateButton.hidden = true;
            addButton.hidden = false;

            whichActive.classList.remove('active');
            exit.remove();
            input.value = '';
            choosenTaskForEdit = false;
            displayList();
        };
    }
})
/*let addTaskButton = document.querySelector('.newTask__button'),
    inputTask = document.querySelector('.newTask__pole'),
    //newTask = inputTask.value,
    //list = document.querySelector('.tasks'),
    ulList = document.querySelector('.tasks__list')
    ;//deleteButtons = document.getElementsByClassName('task__butt');

    ulList.innerHTML = '';
    let tasksList = [];

const createNewTask = (task) =>{
    let li = document.createElement('li');
    li.setAttribute('class', 'tasks__task task');

    li.innerHTML = `
        <input class="task__checkbox" type="checkbox">
        <span class="task__text">${task}</span>
        <button class="task__butt">X</button>
    `

    return li;
};
const addNewTask = (ul, li) =>{
    ul.append(li);
    tasksList.push(li);
};

addTaskButton.addEventListener('click',()=>{
    let newTask = {//inputTask.value;
        taskText: inputTask.value,
        checked: false
    }
    tasksList.push(newTask);
    if(!newTask)return;

    inputTask.value = '';
    addNewTask(ulList, createNewTask(newTask));
});

const displayList = () => {
    let displayList = '';
    tasksList.forEach((item, index)=>{
        displayList += createNewTask(item.taskText);
    })
}

const deleteTask = task =>{
    task.remove();
}
addNewTask(ulList, createNewTask('walk with girl'));
addNewTask(ulList, createNewTask('walk with girl again'));
*/