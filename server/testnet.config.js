module.exports = {
    apps : [
      {
        name: 'proton-test-bots',
        script: 'dist/index.js',
        node_args : '-r dotenv/config',
        watch: false,
        env: {
          'CHAIN': 'proton-test'
        }
      }
    ]
};