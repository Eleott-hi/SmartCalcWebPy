const handlerVertical = document.querySelector('.handler-vertical');
const handlerHorizontal = document.querySelector('.handler-horizontal');
const item1 = document.querySelector('.item1');
const item2 = document.querySelector('.item2');
const mainContainer = document.querySelector('.main-container');

let isDraggingVertical = false;
let isDraggingHorizontal = false;
let containerWidth;
let containerHeight;
let handlerVerticalWidth;
let handlerHorizontalHeight;
let initialX;
let initialY;

handlerVertical.addEventListener('mousedown', handleVerticalMouseDown);
handlerHorizontal.addEventListener('mousedown', handleHorizontalMouseDown);

function handleVerticalMouseDown(event) {
    isDraggingVertical = true;
    containerWidth = mainContainer.offsetWidth;
    handlerVerticalWidth = handlerVertical.offsetWidth;
    initialX = event.clientX;
}

function handleHorizontalMouseDown(event) {
    isDraggingHorizontal = true;
    containerHeight = mainContainer.offsetHeight;
    handlerHorizontalHeight = handlerHorizontal.offsetHeight;
    initialY = event.clientY;
}

document.addEventListener('mousemove', handleMouseMove);
document.addEventListener('mouseup', handleMouseUp);

function handleMouseMove(event) {
    if (isDraggingVertical) {
        handleVerticalResize(event);
    }

    if (isDraggingHorizontal) {
        handleHorizontalResize(event);
    }
}

function handleVerticalResize(event) {
    const currentX = event.clientX;
    const diffX = currentX - initialX;
    const handlerLeft = Math.max(0, Math.min(containerWidth - handlerVerticalWidth, handlerVertical.offsetLeft + diffX));

    handlerVertical.style.left = handlerLeft + 'px';

    const item1Width = handlerLeft;
    const item2Width = containerWidth - handlerVerticalWidth - item1Width;

    item1.style.flexBasis = `${(item1Width / containerWidth) * 100}%`;
    item2.style.flexBasis = `${(item2Width / containerWidth) * 100}%`;

    initialX = currentX;
}

function handleHorizontalResize(event) {
    const currentY = event.clientY;
    const diffY = currentY - initialY;
    const handlerTop = Math.max(0, Math.min(containerHeight - handlerHorizontalHeight, handlerHorizontal.offsetTop + diffY));

    handlerHorizontal.style.top = handlerTop + 'px';

    const placeholder1Height = handlerTop;
    const placeholder2Height = containerHeight - handlerHorizontalHeight - placeholder1Height;

    document.querySelector('.placeholder1').style.flexBasis = `${(placeholder1Height / containerHeight) * 100}%`;
    document.querySelector('.placeholder2').style.flexBasis = `${(placeholder2Height / containerHeight) * 100}%`;

    initialY = currentY;
}

function handleMouseUp() {
    isDraggingVertical = false;
    isDraggingHorizontal = false;
}