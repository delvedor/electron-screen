'use strict'

module.exports = (function getInfo () {
  if (process.platform === 'win32') {
    const screen = require('./build/Release/electronscreen').getInfo
    return screen
  } else {
    try {
      const screen = require('electron').screen
      return screen.getAllDisplays
    } catch (error) {
      throw new Error('Error: Cannot find module \'electron\'')
    }
  }
}())
