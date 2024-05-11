// Function to generate a random integer between min (inclusive) and max (inclusive)
function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

// Array to store random numbers
let numbers = [];

// Generate 100 random positive integers
for (let i = 0; i < 9000; i++) {
    numbers.push(getRandomInt(1, 8000)); // Change 1 and 1000 to adjust range
}

// Sort the array in ascending order
numbers.sort((a, b) => a - b);

// Print the sorted array
let data = ''; 
numbers.map(number =>{
    data += number + ' ';
})
console.log(data);