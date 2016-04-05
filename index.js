'use strict'

const monitor = require('./build/Release/monitor')

// console.log(monitor.getScreens())

monitor.getInfo((m) => {
  console.log(m)
})

console.log(monitor.getObject('ciao', 'mondo'))

// monitor.getInfo(mon[0])
