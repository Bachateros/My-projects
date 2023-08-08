/**
* Задание 12 - Создать интерфейс StarWars DB для данных из SWAPI. 
* https://swapi.dev/
*
* Используя SWAPI, вывести информацию по всех планетам с пагинацией и возможностью просмотреть доп.
* информацию в модальном окне с дозагрузкой смежных ресурсов из каждой сущности.
*
* Данные для отображения в карточке планеты:
* 1. Наименование (name)
* 2. Диаметр (diameter)
* 3. Население (population)
* 4. Уровень гравитации (gravity)
* 5. Природные зоны (terrain)
* 6. Климатические зоны (climate)
*
* При клике по карточке отображаем в модальном окне всю информацию
* из карточки, а также дополнительную:
* 1. Список фильмов (films)
* - Номер эпизода (episode_id)
* - Название (title)
* - Дата выхода (release_date)
* 2. Список персонажей
* - Имя (name)
* - Пол (gender)
* - День рождения (birth_year)
* - Наименование родного мира (homeworld -> name)
*
* Доп. требования к интерфейсу:
* 1. Выводим 10 карточек на 1 странице
* 2. Пагинация позволяет переключаться между страницами, выводить общее количество страниц и текущие выбранные
* элементы в формате 1-10/60 для 1 страницы или 11-20/60 для второй и т.д.
* 3. Используем Bootstrap для создания интерфейсов.
* 4. Добавить кнопку "Показать все" - по клику загрузит все страницы с планетами и выведет
* информацию о них в един (опцианально)
*/

const list = document.querySelector('.content__list');
const row = list.querySelector('.content__row');
const firstFooterButt = document.querySelector('.footer__btn-group').firstElementChild;
let pageData = [];
let cardID = null;
let pageCounter = 1;
const modalBody = document.querySelector('.modal-body');

const cutNumber = string => +string.match(/\d+/g);
const getBaseURL = () =>{
    return 'https://swapi.dev/api/planets/';
}
const getUrlPage = (pageNumber = 1) =>{
    return 'https://swapi.dev/api/planets/' + `?page=${pageNumber}`;
}
row.addEventListener('click',(e)=>{
    cardID = cutNumber(e.target.parentElement.parentElement.id);
    showMOdalWindow();
})

async function showMOdalWindow(){
    modalBody.innerHTML = ''
    let cardInfo = await makeFetchRequest(getBaseURL()+cardID);
    for (const key in cardInfo) {
        if(Array.isArray(cardInfo[key])){
            let template = `<div class="panel"><div class="panel-heading text-primary text-center">`;
            template+=`${key}:</div><div class="panel-body">`;
            await cardInfo[key].forEach(async function(item){
                // const itemInfo = await makeFetchRequest(item)
                    // .then(res => {
                    //     template += `<p>${res.name}</p>`
                    //     console.log(res.name);
                    //     return res;
                    // });
                // if(response.name){
                //     `name
                //     gender
                //     birth_year
                //     homeworld -> name`
                // }
                template = template +`<p><a href="${item}" class="text-warning">${item}</a></p>`

                console.log(item);
            })
            template+='</div></div>';
            modalBody.insertAdjacentHTML('beforeend', template)
        }else {
            modalBody.insertAdjacentHTML('beforeend', `<p><span class="text-primary">${key} :</span> ${cardInfo[key]}</p>`)
        }
    }
}

// const myModalAlternative = new bootstrap.Modal('#myModal', options)

async function makeFetchRequest(url){
    const response = await fetch(url)
            .then(res => res.text())
            .then(res => JSON.parse(res))
            .catch(e => console.error(e))
    return response;
}
async function getPageData(pageNumber){
    pageData = [];
    const response = await makeFetchRequest(getUrlPage(pageNumber))
    await response.results.forEach( item => pageData.push(item))
    return response;
}
async function setPageData(pageNumber){
    row.innerHTML = '';
    await getPageData(pageNumber);
    pageData.forEach(item => {
        row.insertAdjacentHTML('beforeend', 
`<div class="content__card card" id="card_${cutNumber(item.url)}">
<div class="card-body">
    <h5 class="card-title">${item.name}</h5>
    <p class="card-text">diameter: ${item.diameter}</p>
    <p class="card-text">population: ${item.population}</p>
    <p class="card-text">gravity: ${item.gravity}</p>
    <p class="card-text">terrain: ${item.terrain}</p>
    <p class="card-text">climate: ${item.climate}</p>
    <a href="#" class="card__butt btn btn-primary" data-bs-toggle="modal" data-bs-target="#staticBackdrop">Подробнее</a>
</div>
</div>`)
    });
    return pageData;
}

async function setCountButt(){
    let response = await makeFetchRequest(getUrlPage())
    const totalPageCounter = Math.ceil(response.count / 10)
    for(let i = totalPageCounter; i > 0; i--){
        firstFooterButt.insertAdjacentHTML('afterend', 
            `<button class="footer__butt btn btn-light text-capitalize ${i == pageCounter? 'active': ''}" id="${i}">${i}</button>`)
    }
    const buttonsGroup = firstFooterButt.parentElement;
    buttonsGroup.addEventListener('click',(event)=>{
        if(event.target.id == 0 && pageCounter > 1){
            pageCounter--
            setPageData(pageCounter)
            
        }
        if(event.target.id == -1 && pageCounter < totalPageCounter){
            pageCounter++
            setPageData(pageCounter)
        }
        if(event.target.id > 0 && event.target.id <= totalPageCounter){
            pageCounter = event.target.id;
            event.target.classList.add('active')
            setPageData(pageCounter)
        }
    })
    return totalPageCounter;
}

function startApp(){
    setPageData();
    setCountButt()
}
startApp();